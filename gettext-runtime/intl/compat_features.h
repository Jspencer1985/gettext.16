#ifndef COMPAT_FEATURES_H
#define COMPAT_FEATURES_H



#ifndef __BEGIN_NAMESPACE_STD
#define __BEGIN_NAMESPACE_STD
#endif

#ifndef __END_NAMESPACE_STD
#define __END_NAMESPACE_STD
#endif

#ifndef __THROW
#define __THROW
#endif

#ifndef __nonnull
#define __nonnull(params)
#endif

#ifndef __attribute_pure__
#define __attribute_pure__
#endif

#ifndef __attribute_malloc__
#define __attribute_malloc__
#endif

#ifndef IS_IN
#define IS_IN(lib) 0
#endif

#ifndef libc_hidden_proto
#define libc_hidden_proto(name)
#endif

#endif // __APPLE__