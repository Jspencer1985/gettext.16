#ifndef FIX_MACROS_H
#define FIX_MACROS_H

/* Remove the pragma message as it's causing warnings */
/* #pragma message("Including fix_macros.h") */

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

#endif /* FIX_MACROS_H */
