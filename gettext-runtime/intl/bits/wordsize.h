#ifndef _BITS_WORDSIZE_H
#define _BITS_WORDSIZE_H 1

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__powerpc64__)
# define __WORDSIZE 64
#else
# define __WORDSIZE 32
#endif

#endif /* _BITS_WORDSIZE_H */