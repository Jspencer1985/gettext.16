#include <stdio.h>
#include <stdarg.h>
#include "libintl.h"

/* Implementation of the printf wrapper functions */
int libintl_printf(const char *format, ...) {
    va_list args;
    int result;
    
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    
    return result;
}

int libintl_vprintf(va_list args, const char *format) {
    return vprintf(format, args);
}

int libintl_fprintf(FILE *stream, const char *format, ...) {
    va_list args;
    int result;
    
    va_start(args, format);
    result = vfprintf(stream, format, args);
    va_end(args);
    
    return result;
}

int libintl_vfprintf(FILE *stream, const char *format, va_list args) {
    return vfprintf(stream, format, args);
}