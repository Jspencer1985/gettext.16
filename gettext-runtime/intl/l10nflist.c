/* Copyright (C) 1995-1999, 2000-2006 Free Software Foundation, Inc.
   Contributed by Ulrich Drepper <drepper@gnu.ai.mit.edu>, 1995.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
   USA.  */

/* Tell glibc's <string.h> to provide a prototype for stpcpy().
   This must come before <config.h> because <config.h> may include
   <features.h>, and once <features.h> has been included, it's too late.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE	1
#endif

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <string.h>

#if defined _LIBC || defined HAVE_ARGZ_H
# include <argz.h>
#endif
#include <ctype.h>
#include <sys/types.h>
#include <stdlib.h>

#include "loadinfo.h"

/* On some strange systems still no definition of NULL is found.  Sigh!  */
#ifndef NULL
# if defined __STDC__ && __STDC__
#  define NULL ((void *) 0)
# else
#  define NULL 0
# endif
#endif

/* @@ end of prolog @@ */

/* Explicitly declare stpcpy for all configurations */
#if !defined HAVE_STPCPY || !defined _LIBC
char *stpcpy (char *dest, const char *src);
#endif

#ifdef _LIBC
/* Rename the non ANSI C functions.  This is required by the standard
   because some ANSI C functions will require linking with this object
   file and the name space must not be polluted.  */
# ifndef stpcpy
#  define stpcpy(dest, src) __stpcpy(dest, src)
# endif
#endif

/* Pathname support.
   ISSLASH(C)           tests whether C is a directory separator character.
   IS_ABSOLUTE_PATH(P)  tests whether P is an absolute path.  If it is not,
                        it may be concatenated to a directory pathname.
 */
#if defined _WIN32 || defined __WIN32__ || defined __CYGWIN__ || defined __EMX__ || defined __DJGPP__
  /* Win32, Cygwin, OS/2, DOS */
# define ISSLASH(C) ((C) == '/' || (C) == '\\')
# define HAS_DEVICE(P) \
    ((((P)[0] >= 'A' && (P)[0] <= 'Z') || ((P)[0] >= 'a' && (P)[0] <= 'z')) \
     && (P)[1] == ':')
# define IS_ABSOLUTE_PATH(P) (ISSLASH ((P)[0]) || HAS_DEVICE (P))
#else
  /* Unix */
# define ISSLASH(C) ((C) == '/')
# define IS_ABSOLUTE_PATH(P) ISSLASH ((P)[0])
#endif

/* Define function which are usually not available.  */

#ifdef _LIBC
# define __argz_count(argz, len) INTUSE(__argz_count) (argz, len)
#elif defined HAVE_ARGZ_COUNT
# undef __argz_count
# define __argz_count argz_count
#else
/* Returns the number of strings in ARGZ.  */
static size_t
argz_count__ (const char *argz, size_t len)
{
  size_t count = 0;
  while (len > 0)
    {
      size_t part_len = strlen (argz);
      argz += part_len + 1;
      len -= part_len + 1;
      count++;
    }
  return count;
}
# undef __argz_count
# define __argz_count(argz, len) argz_count__ (argz, len)
#endif	/* !_LIBC && !HAVE_ARGZ_COUNT */

#ifdef _LIBC
# define __argz_stringify(argz, len, sep) \
  INTUSE(__argz_stringify) (argz, len, sep)
#elif defined HAVE_ARGZ_STRINGIFY
# undef __argz_stringify
# define __argz_stringify argz_stringify
#else
/* Make '\0' separated arg vector ARGZ printable by converting all the '\0's
   except the last into the character SEP.  */
static void
argz_stringify__ (char *argz, size_t len, int sep)
{
  while (len > 0)
    {
      size_t part_len = strlen (argz);
      argz += part_len;
      len -= part_len + 1;
      if (len > 0)
	*argz++ = sep;
    }
}
# undef __argz_stringify
# define __argz_stringify(argz, len, sep) argz_stringify__ (argz, len, sep)
#endif	/* !_LIBC && !HAVE_ARGZ_STRINGIFY */

#ifdef _LIBC
#elif defined HAVE_ARGZ_NEXT
# undef __argz_next
# define __argz_next argz_next
#else
static char *
argz_next__ (char *argz, size_t argz_len, const char *entry)
{
  if (entry)
    {
      if (entry < argz + argz_len)
        entry = strchr (entry, '\0') + 1;

      return entry >= argz + argz_len ? NULL : (char *) entry;
    }
  else
    if (argz_len > 0)
      return argz;
    else
      return 0;
}
# undef __argz_next
# define __argz_next(argz, len, entry) argz_next__ (argz, len, entry)
#endif	/* !_LIBC && !HAVE_ARGZ_NEXT */


/* Return number of bits set in X.  */
static inline int
pop (int x)
{
  /* We assume that no more than 16 bits are used.  */
  x = ((x & ~0x5555) >> 1) + (x & 0x5555);
  x = ((x & ~0x3333) >> 2) + (x & 0x3333);
  x = ((x >> 4) + x) & 0x0f0f;
  x = ((x >> 8) + x) & 0xff;

  return x;
}


struct loaded_l10nfile *
_nl_make_l10nflist (struct loaded_l10nfile **l10nfile_list,
		    const char *dirlist, size_t dirlist_len,
		    int mask, const char *language, const char *territory,
		    const char *codeset, const char *normalized_codeset,
		    const char *modifier,
		    const char *filename, int do_allocate)
{
  char *abs_filename;
  struct loaded_l10nfile **lastp;
  struct loaded_l10nfile *retval;
  char *cp;
  size_t dirlist_count;
  size_t entries;
  int cnt;

  /* If LANGUAGE contains an absolute directory specification, we ignore
     DIRLIST.  */
  if (IS_ABSOLUTE_PATH (language))
    dirlist_len = 0;

  /* Allocate room for the full file name.  */
  abs_filename = (char *) malloc (dirlist_len
				  + strlen (language)
				  + ((mask & XPG_TERRITORY) != 0
				     ? strlen (territory) + 1 : 0)
				  + ((mask & XPG_CODESET) != 0
				     ? strlen (codeset) + 1 : 0)
				  + ((mask & XPG_NORM_CODESET) != 0
				     ? strlen (normalized_codeset) + 1 : 0)
				  + ((mask & XPG_MODIFIER) != 0
				     ? strlen (modifier) + 1 : 0)
				  + 1 + strlen (filename) + 1);

  if (abs_filename == NULL)
    return NULL;

  /* Construct file name.  */
  cp = abs_filename;
  if (dirlist_len > 0)
    {
      memcpy (cp, dirlist, dirlist_len);
      __argz_stringify (cp, dirlist_len, PATH_SEPARATOR);
      cp += dirlist_len;
      cp[-1] = '/';
    }

  cp = stpcpy (cp, language);

  if ((mask & XPG_TERRITORY) != 0)
    {
      *cp++ = '_';
      cp = stpcpy (cp, territory);
    }
  if ((mask & XPG_CODESET) != 0)
    {
      *cp++ = '.';
      cp = stpcpy (cp, codeset);
    }
  if ((mask & XPG_NORM_CODESET) != 0)
    {
      *cp++ = '.';
      cp = stpcpy (cp, normalized_codeset);
    }
  if ((mask & XPG_MODIFIER) != 0)
    {
      *cp++ = '@';
      cp = stpcpy (cp, modifier);
    }

  *cp++ = '/';
  stpcpy (cp, filename);

  /* Look in list of already loaded domains whether it is already
     available.  */
  lastp = l10nfile_list;
  for (retval = *l10nfile_list; retval != NULL; retval = retval->next)
    if (retval->filename != NULL)
      {
	int compare = strcmp (retval->filename, abs_filename);
	if (compare == 0)
	  /* We found it!  */
	  break;
	if (compare < 0)
	  {
	    /* It's not in the list.  */
	    retval = NULL;
	    break;
	  }

	lastp = &retval->next;
      }

  if (retval != NULL || do_allocate == 0)
    {
      free (abs_filename);
      return retval;
    }

  dirlist_count = (dirlist_len > 0 ? __argz_count (dirlist, dirlist_len) : 1);

  /* Allocate a new loaded_l10nfile.  */
  retval =
    (struct loaded_l10nfile *)
    malloc (sizeof (*retval)
	    + (((dirlist_count << pop (mask)) + (dirlist_count > 1 ? 1 : 0))
	       * sizeof (struct loaded_l10nfile *)));
  if (retval == NULL)
    {
      free (abs_filename);
      return NULL;
    }

  retval->filename = abs_filename;

  /* We set retval->data to NULL here; it is filled in later.
     Setting retval->decided to 1 here means that retval does not
     correspond to a real file (dirlist_count > 1) or is not worth
     looking up (if an unnormalized codeset was specified).  */
  retval->decided = (dirlist_count > 1
		     || ((mask & XPG_CODESET) != 0
			 && (mask & XPG_NORM_CODESET) != 0));
  retval->data = NULL;

  retval->next = *lastp;
  *lastp = retval;

  entries = 0;
  /* Recurse to fill the inheritance list of RETVAL.
     If the DIRLIST is a real list (i.e. DIRLIST_COUNT > 1), the RETVAL
     entry does not correspond to a real file; retval->filename contains
     colons.  In this case we loop across all elements of DIRLIST and
     across all bit patterns dominated by MASK.
     If the DIRLIST is a single directory or entirely redundant (i.e.
     DIRLIST_COUNT == 1), we loop across all bit patterns dominated by
     MASK, excluding MASK itself.
     In either case, we loop down from MASK to 0.  This has the effect
     that the extra bits in the locale name are dropped in this order:
     first the modifier, then the territory, then the codeset, then the
     normalized_codeset.  */
  for (cnt = dirlist_count > 1 ? mask : mask - 1; cnt >= 0; --cnt)
    if ((cnt & ~mask) == 0
	&& !((cnt & XPG_CODESET) != 0 && (cnt & XPG_NORM_CODESET) != 0))
      {
	if (dirlist_count > 1)
	  {
	    /* Iterate over all elements of the DIRLIST.  */
	    char *dir = NULL;

	    while ((dir = __argz_next ((char *) dirlist, dirlist_len, dir))
		   != NULL)
	      retval->successor[entries++]
		= _nl_make_l10nflist (l10nfile_list, dir, strlen (dir) + 1,
				      cnt, language, territory, codeset,
				      normalized_codeset, modifier, filename,
				      1);
	  }
	else
	  retval->successor[entries++]
	    = _nl_make_l10nflist (l10nfile_list, dirlist, dirlist_len,
				  cnt, language, territory, codeset,
				  normalized_codeset, modifier, filename, 1);
      }
  retval->successor[entries] = NULL;

  return retval;
}

/* Normalize codeset name.  There is no standard for the codeset
   names.  Normalization allows the user to use any of the common
   names.  The return value is dynamically allocated and has to be
   freed by the caller.  */
const char *
_nl_normalize_codeset (const char *codeset, size_t name_len)
{
  int len = 0;
  int only_digit = 1;
  char *retval;
  char *wp;
  size_t cnt;

  for (cnt = 0; cnt < name_len; ++cnt)
    if (isalnum ((unsigned char) codeset[cnt]))
      {
	++len;

	if (isalpha ((unsigned char) codeset[cnt]))
	  only_digit = 0;
      }

  retval = (char *) malloc ((only_digit ? 3 : 0) + len + 1);

  if (retval != NULL)
    {
      if (only_digit)
	wp = stpcpy (retval, "iso");
      else
	wp = retval;

      for (cnt = 0; cnt < name_len; ++cnt)
	if (isalpha ((unsigned char) codeset[cnt]))
	  *wp++ = tolower ((unsigned char) codeset[cnt]);
	else if (isdigit ((unsigned char) codeset[cnt]))
	  *wp++ = codeset[cnt];

      *wp = '\0';
    }

  return (const char *) retval;
}


/* @@ begin of epilog @@ */

/* We don't want libintl.a to depend on any other library.  So we
   avoid the non-standard function stpcpy.  In GNU C Library this
   function is available, though.  Also allow the symbol HAVE_STPCPY
   to be defined.  */
#if !_LIBC && !HAVE_STPCPY
static char *
stpcpy (char *dest, const char *src)
{
  while ((*dest++ = *src++) != '\0')
    /* Do nothing. */ ;
  return dest - 1;
}
#endif
