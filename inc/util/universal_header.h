#   if !defined(ALIGN) && defined(__GNUC__)
#     define ALIGN(x) __attribute__ ((aligned (x)))
#   elif !defined(ALIGN) && defined(_MSC_VER)
#     define ALIGN(x) __declspec(align(x))
#   endif /* ALIGN */
#   ifdef   UNICODE
#     define  PREFIX_L(x) L ## x
typedef wchar_t tchar_t;
#   else
#     define  PREFIX_L(x) x
typedef char tchar_t;
#   endif /* UNICODE */
#   if !defined(NULL) && defined(__cplusplus)
#     define  NULL  nullptr
#   elif !defined(NULL) && !defined(__cplusplus)
#     define  NULL  0U
#   endif /* NULL */
#   ifndef  _GLIBCXX_VISIBILITY
#     define _GLIBCXX_VISIBILITY(V) __attribute__ ((__visibility__ (#V)))
#   endif /* _GLIBCXX_VISIBILITY */
#   if defined(_COMPILING_COMMON_) && defined(WIN32)
#     define LIBSPEC __declspec(dllexport)
#   elif !defined(_COMPILING_COMMON_) && defined(WIN32)
#     define LIBSPEC __declspec(dllimport)
#   else
#     define LIBSPEC
#   endif /* _COMPILING_COMMON_H_ */
#   ifdef WIN32
#     define LINKAGE __stdcall
#   else
#     define LINKAGE
#   endif /* LINKAGE */