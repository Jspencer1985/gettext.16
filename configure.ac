dnl Configuration for the toplevel directory of GNU gettext
dnl Copyright (C) 1995-1999, 2000-2003, 2005-2006 Free Software Foundation, Inc.
dnl
dnl This program is free software; you can redistribute it and/or modify
dnl it under the terms of the GNU General Public License as published by
dnl the Free Software Foundation; either version 2, or (at your option)
dnl any later version.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
dnl GNU General Public License for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([gettext],[0.16],[bug-gettext@gnu.org])
AC_CONFIG_SRCDIR(gettext-tools/src/msgfmt.c)
AC_CONFIG_AUX_DIR(build-aux)
. $srcdir/version.sh
AM_INIT_AUTOMAKE([1.11 gnu no-dependencies])

dnl Checks for programs.

dnl Checks for libraries.

dnl Checks for header files.

dnl Checks for typedefs, structures, and compiler characteristics.

dnl Checks for library functions.

AC_CONFIG_SUBDIRS(autoconf-lib-link gettext-runtime gettext-tools)

dnl Ensure that "configure --help" lists all the command line options that
dnl are usable with the subdir configures. Really AC_CONFIG_SUBDIRS should
dnl do it by itself.
dnl System types:
AC_CANONICAL_HOST
dnl Optional Features: AC_ARG_ENABLE calls
dnl Optional Packages: AC_ARG_WITH calls
dnl Some influential environment variables: AC_ARG_VAR calls
esyscmd([{ cd autoconf-lib-link && autoconf --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..; cd gettext-runtime && autoconf --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..; cd gettext-tools && autoconf --trace=AC_ARG_ENABLE:'$n([$1],[$2])' --trace=AC_ARG_WITH:'$n([$1],[$2])' --trace=AC_ARG_VAR:'$n($@)' && cd ..; } | sed -f build-aux/ac-help.sed ])

AC_CONFIG_FILES([Makefile])

AC_CONFIG_FILES([gnulib-local/Makefile])

AC_OUTPUT
