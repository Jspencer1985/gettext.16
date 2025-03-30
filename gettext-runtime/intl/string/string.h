/*
* ISO C99 Standard: 7.21 String handling <string.h>
*/
#include "../fix_macros.h"  // Ensure the correct relative path

/*
* ISO C99 Standard: 7.21 String handling <string.h>
*/
#ifndef _STRING_STRING_H
#define _STRING_STRING_H 1

   Return the position in DEST one byte past where C was copied,
   or NULL if C was not found in the first N bytes of SRC.  */
/* Copy N bytes of SRC to DEST. */
extern void *memcpy (void *dest, const void *src, size_t n);

/* Compare N bytes of S1 and S2.  */
   correct behavior for overlapping strings. */
extern void *memmove (void *dest, const void *src, size_t n);
/* Compare N bytes of S1 and S2.  Return zero if S1 and S2 are equal.
   Return some non-zero value otherwise.

   or NULL if C was not found in the first N bytes of SRC. */
extern void *memccpy (void *dest, const void *src, int c, size_t n);

/* Set N bytes of S to C. */
extern void *memset (void *s, int c, size_t n);
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
/* Compare N bytes of S1 and S2. */
extern int memcmp (const void *s1, const void *s2, size_t n);
#ifdef __CORRECT_ISO_CPP_STRING_H_PROTO
/* Search N bytes of S for C. */
extern void *memchr (const void *s, int c, size_t n);

/* Copy SRC to DEST. */
extern char *strcpy (char *dest, const char *src);

/* Copy no more than N characters of SRC to DEST. */
extern char *strncpy (char *dest, const char *src, size_t n);
/* Put a transformation of SRC into no more than N bytes of DEST.  */
/* Append SRC onto DEST. */
extern char *strcat (char *dest, const char *src);

/* Append no more than N characters from SRC onto DEST. */
extern char *strncat (char *dest, const char *src, size_t n);
# include <bits/types/locale_t.h>
/* Compare S1 and S2. */
extern int strcmp (const char *s1, const char *s2);

/* Compare N characters of S1 and S2. */
extern int strncmp (const char *s1, const char *s2, size_t n);
# ifdef __OPTIMIZE__
__extern_always_inline char *
   consists entirely of characters not in REJECT. */
extern size_t strcspn (const char *s, const char *reject);

}
   consists entirely of characters in ACCEPT. */
extern size_t strspn (const char *s, const char *accept);

/* Find the first occurrence of C in S. */
extern char *strchr (const char *s, int c);

/* Find the last occurrence of C in S. */
extern char *strrchr (const char *s, int c);

/* Return the length of S. */
extern size_t strlen (const char *s);

#endif /* _STRING_STRING_H */
