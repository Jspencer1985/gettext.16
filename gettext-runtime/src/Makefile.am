## Makefile for the gettext-runtime/src subdirectory of GNU gettext
## Copyright (C) 1995-1998, 2000-2006 Free Software Foundation, Inc.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software Foundation,
## Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

## Process this file with automake to produce Makefile.in.

AUTOMAKE_OPTIONS = 1.5 gnits no-dependencies
EXTRA_DIST =
DISTCLEANFILES =

RM = rm -f

bin_PROGRAMS = gettext ngettext envsubst

AM_CPPFLAGS = \
  -I. -I$(srcdir) \
  -I.. \
  -I../intl -I$(srcdir)/../intl \
  -I../gnulib-lib -I$(srcdir)/../gnulib-lib
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

# Source dependencies.
gettext_SOURCES = gettext.c
ngettext_SOURCES = ngettext.c
envsubst_SOURCES = envsubst.c

# Link dependencies.
# Need @LTLIBICONV@ because striconv.c uses iconv().
LDADD = ../gnulib-lib/libgrt.la @LTLIBINTL@ @LTLIBICONV@

# Add explicit object files if libgrt.a is being ignored
gettext_LDADD = $(LDADD) \
  ../gnulib-lib/close-stream.o \
  ../gnulib-lib/closeout.o \
  ../gnulib-lib/error.o \
  ../gnulib-lib/basename-lgpl.o \
  ../gnulib-lib/progname.o \
  ../gnulib-lib/getopt.o \
  ../gnulib-lib/getopt1.o \
  ../gnulib-lib/xmalloc.o

# Specify installation directory, for --enable-relocatable.
gettext_CFLAGS = -DINSTALLDIR=\"$(bindir)\"
ngettext_CFLAGS = -DINSTALLDIR=\"$(bindir)\"
envsubst_CFLAGS = -DINSTALLDIR=\"$(bindir)\"
if RELOCATABLE_VIA_LD
gettext_LDFLAGS = `$(RELOCATABLE_LDFLAGS) $(bindir)`
ngettext_LDFLAGS = `$(RELOCATABLE_LDFLAGS) $(bindir)`
envsubst_LDFLAGS = `$(RELOCATABLE_LDFLAGS) $(bindir)`
endif

# For installing gettext.sh in $(bindir).
bin_SCRIPTS = gettext.sh
DISTCLEANFILES += gettext.sh

# Support for relocatability.
RELOCATABLE_LIBRARY_PATH = $(libdir)
RELOCATABLE_SRC_DIR = $(top_srcdir)/gnulib-lib
RELOCATABLE_BUILD_DIR = ../gnulib-lib
RELOCATABLE_CONFIG_H_DIR = ..
@SET_RELOCATABLE@
