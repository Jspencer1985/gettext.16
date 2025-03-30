/* Replace the entire file with a simplified version */
#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

/* Basic string functions */
extern void *memcpy(void *dest, const void *src, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern int memcmp(const void *s1, const void *s2, size_t n);
extern void *memset(void *s, int c, size_t n);

extern char *strcpy(char *dest, const char *src);
extern char *strncpy(char *dest, const char *src, size_t n);
extern char *strcat(char *dest, const char *src);
extern char *strncat(char *dest, const char *src, size_t n);
extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, size_t n);
extern char *strchr(const char *s, int c);
extern char *strrchr(const char *s, int c);
extern size_t strlen(const char *s);
extern size_t strnlen(const char *string, size_t maxlen);
extern char *strerror(int errnum);
extern char *strerror_r(int errnum, char *buf, size_t buflen);
extern char *strdup(const char *s);

#endif /* _STRING_H */
