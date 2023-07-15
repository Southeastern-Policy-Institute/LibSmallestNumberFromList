/* FILENAME.H - Description
 * AUTHOR
 * Southeastern Policy Institute, 2023
 */

# ifndef _SMALLESTNUMBERFROMLIST_FILENAME_H_
#   define _SMALLESTNUMBERFROMLIST_FILENAME_H_
#   if _MSC_VER > 1000
#     pragma once
#   endif /* _MSC_VER */
    /* Include Files Here */
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
#   ifdef __cplusplus
namespace namespacename {

  /* C++ exclusive code here */

  extern "C" {
#   endif /* __cplusplus */

    /* C compatible function calls go here */

    /* An example of how to properly declare a public-facing function:
    * LIBSPEC LINKAGE unsigned int rpg_RNG (void);
    * This is for Windows DLL compatibility.
    */

#   undef LINKAGE
#   undef LIBSPEC
#   ifdef __cplusplus
  };
};
#   endif /* __cplusplus */
# endif /* _SMALLESTNUMBERFROMLIST_FILENAME_H_ */
