#!/bin/bash
# Build gettext with printf wrappers

cd build/gettext-runtime/src

# Compile the wrapper functions
gcc -c printf-wrapper.c -o printf-wrapper.o

# Compile closeout.c for envsubst
gcc -c closeout.c -o closeout.o

# Compile gettext if needed
if [ ! -f gettext-gettext.o ]; then
  gcc -DLOCALEDIR=\"/usr/local/share/locale\" -DHAVE_CONFIG_H -I. -I.. -I../../../gettext-runtime/src -I../intl -I../../../gettext-runtime/src/../intl -I../gnulib-lib -I../../../gettext-runtime/src/../gnulib-lib -I/usr/local/include -DINSTALLDIR=\"/usr/local/bin\" -g -O2 -c ../../../gettext-runtime/src/gettext.c -o gettext-gettext.o
fi

# Compile ngettext if needed
if [ ! -f ngettext-ngettext.o ]; then
  gcc -DLOCALEDIR=\"/usr/local/share/locale\" -DHAVE_CONFIG_H -I. -I.. -I../../../gettext-runtime/src -I../intl -I../../../gettext-runtime/src/../intl -I../gnulib-lib -I../../../gettext-runtime/src/../gnulib-lib -I/usr/local/include -DINSTALLDIR=\"/usr/local/bin\" -g -O2 -c ../../../gettext-runtime/src/ngettext.c -o ngettext-ngettext.o
fi

# Compile envsubst if needed
if [ ! -f envsubst-envsubst.o ]; then
  gcc -DLOCALEDIR=\"/usr/local/share/locale\" -DHAVE_CONFIG_H -I. -I.. -I../../../gettext-runtime/src -I../intl -I../../../gettext-runtime/src/../intl -I../gnulib-lib -I../../../gettext-runtime/src/../gnulib-lib -I/usr/local/include -DINSTALLDIR=\"/usr/local/bin\" -g -O2 -c ../../../gettext-runtime/src/envsubst.c -o envsubst-envsubst.o
fi

# Link gettext
gcc -DINSTALLDIR=\"/usr/local/bin\" -g -O2 -o gettext gettext-gettext.o printf-wrapper.o \
  ../gnulib-lib/libgrt.a ../intl/.libs/libintl.dylib \
  -L/usr/local/lib -liconv -Wl,-framework -Wl,CoreFoundation

# Link ngettext
gcc -DINSTALLDIR=\"/usr/local/bin\" -g -O2 -o ngettext ngettext-ngettext.o printf-wrapper.o \
  ../gnulib-lib/libgrt.a ../intl/.libs/libintl.dylib \
  -L/usr/local/lib -liconv -Wl,-framework -Wl,CoreFoundation

# Link envsubst (only if compilation succeeded)
if [ -f envsubst-envsubst.o ]; then
  gcc -DINSTALLDIR=\"/usr/local/bin\" -g -O2 -o envsubst envsubst-envsubst.o printf-wrapper.o closeout.o \
    ../gnulib-lib/libgrt.a ../intl/.libs/libintl.dylib \
    -L/usr/local/lib -liconv -Wl,-framework -Wl,CoreFoundation
fi

echo "Build completed. Check for errors above."
