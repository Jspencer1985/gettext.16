/* Find the length of STRING + 1, but scan at most MAXLEN bytes.
   Copyright (C) 2005-2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#include <config.h>

/* Specification.  */
#include "strnlen1.h"

#include <string.h>

/* Explicitly declare memchr if the include isn't working */
#ifndef memchr
void *memchr(const void *s, int c, size_t n);
#endif

/* Find the length of STRING + 1, but scan at most MAXLEN bytes.
   If no '\0' terminator is found in that many characters, return MAXLEN.  */
/* This is the same as strnlen (string, maxlen - 1) + 1.  */
size_t
strnlen1 (const char *string, size_t maxlen)
{
  const char *end = memchr (string, '\0', maxlen);
  if (end != NULL)
    return end - string + 1;
  else
    return maxlen;
}
