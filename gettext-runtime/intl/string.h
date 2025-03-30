/* Replace the entire file with a simplified version */
#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

/* Basic string functions without GNU extensions */
extern void *memcpy (void *dest, const void *src, size_t n);
extern size_t strlen (const char *s);
extern size_t strnlen (const char *string, size_t maxlen);
extern char *strerror_r (int errnum, char *buf, size_t buflen);

/* Include the system string.h for the rest of the definitions */
#include "string/string.h"

#endif /* _STRING_H */
