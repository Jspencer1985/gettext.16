#ifndef FIX_MACROS_H
#define FIX_MACROS_H

/* Define all the GNU-specific attributes as empty macros */
#ifndef __THROW
#define __THROW
#endif

#ifndef __nonnull
#define __nonnull(...)
#endif

#ifndef __attribute_pure__
#define __attribute_pure__
#endif

#ifndef __attr_access
#define __attr_access(...)
#endif

#ifndef __attribute_malloc__
#define __attribute_malloc__
#endif

/* Force the use of system string.h instead of custom one */
#define _STRING_H 1
#define _STRING_STRING_H 1

#endif /* FIX_MACROS_H */
