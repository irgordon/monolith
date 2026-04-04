#ifndef OS_COMPILER_H
#define OS_COMPILER_H

#if defined(__cplusplus)
#define OS_EXTERN_C_BEGIN extern "C" {
#define OS_EXTERN_C_END   }
#else
#define OS_EXTERN_C_BEGIN
#define OS_EXTERN_C_END
#endif

#if defined(__has_c_attribute)
#if __has_c_attribute(noreturn)
#define OS_NORETURN [[noreturn]]
#endif
#endif
#ifndef OS_NORETURN
#if defined(__GNUC__) || defined(__clang__)
#define OS_NORETURN __attribute__((__noreturn__))
#elif defined(_MSC_VER)
#define OS_NORETURN __declspec(noreturn)
#else
#define OS_NORETURN
#endif
#endif

#if defined(__has_c_attribute)
#if __has_c_attribute(maybe_unused)
#define OS_UNUSED [[maybe_unused]]
#endif
#endif
#ifndef OS_UNUSED
#if defined(__GNUC__) || defined(__clang__)
#define OS_UNUSED __attribute__((__unused__))
#else
#define OS_UNUSED
#endif
#endif

#endif /* OS_COMPILER_H */
