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

/* Define attribute_hidden as empty */
#ifndef attribute_hidden
#define attribute_hidden
#endif

/* Define rwlock macros */
#ifndef gl_rwlock_define
#define gl_rwlock_define(scope, name) scope pthread_rwlock_t name
#endif

#ifndef gl_rwlock_wrlock
#define gl_rwlock_wrlock(lock) pthread_rwlock_wrlock(&(lock))
#endif

#ifndef gl_rwlock_unlock
#define gl_rwlock_unlock(lock) pthread_rwlock_unlock(&(lock))
#endif

/* Include pthread.h for rwlock definitions */
#include <pthread.h>

/* Include standard string.h */
#include <string.h>

/* Define strdup if it's not available in the system header */
#ifndef strdup
extern char *strdup(const char *s);
#endif

#endif /* FIX_MACROS_H */
