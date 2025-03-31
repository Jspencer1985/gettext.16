# gnulib_stpncpy.m4 serial 4
dnl Copyright (C) 2002-2003, 2005-2006 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_gnulib_stpncpy],
[
  dnl Persuade glibc <string.h> to declare gnulib_stpncpy().
  AC_REQUIRE([AC_GNU_SOURCE])

  dnl Both glibc and AIX (4.3.3, 5.1) have an gnulib_stpncpy() function
  dnl declared in <string.h>. Its side effects are the same as those
  dnl of strncpy():
  dnl      gnulib_stpncpy (dest, src, n)
  dnl overwrites dest[0..n-1], min(strlen(src),n) bytes coming from src,
  dnl and the remaining bytes being NULs.  However, the return value is
  dnl   in glibc:   dest + min(strlen(src),n)
  dnl   in AIX:     dest + max(0,n-1)
  dnl Only the glibc return value is useful in practice.

  AC_CACHE_CHECK([for working gnulib_stpncpy], gl_cv_func_gnulib_stpncpy, [
    AC_TRY_RUN([
#include <stdlib.h>
#include <string.h> /* for strcpy */
/* The gnulib_stpncpy prototype is missing in <string.h> on AIX 4.  */
extern char *gnulib_stpncpy (char *dest, const char *src, size_t n);
int main () {
  const char *src = "Hello";
  char dest[10];
  /* AIX 4.3.3 and AIX 5.1 gnulib_stpncpy() returns dest+1 here.  */
  strcpy (dest, "\377\377\377\377\377\377");
  if (gnulib_stpncpy (dest, src, 2) != dest + 2) exit(1);
  /* AIX 4.3.3 and AIX 5.1 gnulib_stpncpy() returns dest+4 here.  */
  strcpy (dest, "\377\377\377\377\377\377");
  if (gnulib_stpncpy (dest, src, 5) != dest + 5) exit(1);
  /* AIX 4.3.3 and AIX 5.1 gnulib_stpncpy() returns dest+6 here.  */
  strcpy (dest, "\377\377\377\377\377\377");
  if (gnulib_stpncpy (dest, src, 7) != dest + 5) exit(1);
  exit(0);
}
], gl_cv_func_gnulib_stpncpy=yes, gl_cv_func_gnulib_stpncpy=no,
  [AC_EGREP_CPP([Thanks for using GNU], [
#include <features.h>
#ifdef __GNU_LIBRARY__
  Thanks for using GNU
#endif
], gl_cv_func_gnulib_stpncpy=yes, gl_cv_func_gnulib_stpncpy=no)])])

  if test $gl_cv_func_gnulib_stpncpy = yes; then
    AC_DEFINE(HAVE_gnulib_stpncpy, 1,
      [Define if you have the gnulib_stpncpy() function and it works.])
  else
    AC_LIBOBJ([gnulib_stpncpy])
    gl_PREREQ_gnulib_stpncpy
  fi
])

# Prerequisites of lib/gnulib_stpncpy.c.
AC_DEFUN([gl_PREREQ_gnulib_stpncpy], [
  :
])

