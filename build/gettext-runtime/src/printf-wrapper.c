#include <stdio.h>
#include <stdarg.h>

/* Wrapper functions for printf and fprintf */
int libintl_printf(const char *format, ...) {
    va_list args;
    int result;
    
    va_start(args, format);
    result = vprintf(format, args);
    va_end(args);
    
    return result;
}

int libintl_fprintf(FILE *stream, const char *format, ...) {
    va_list args;
    int result;
    
    va_start(args, format);
    result = vfprintf(stream, format, args);
    va_end(args);
    
    return result;
}

/* Additional wrapper functions that might be needed */
int libintl_vfprintf(FILE *stream, const char *format, va_list args) {
    return vfprintf(stream, format, args);
}

int libintl_vprintf(const char *format, va_list args) {
    return vprintf(format, args);
}

int libintl_sprintf(char *str, const char *format, ...) {
    va_list args;
    int result;
    
    va_start(args, format);
    result = vsprintf(str, format, args);
    va_end(args);
    
    return result;
}

int libintl_snprintf(char *str, size_t size, const char *format, ...) {
    va_list args;
    int result;
    
    va_start(args, format);
    result = vsnprintf(str, size, format, args);
    va_end(args);
    
    return result;
}
