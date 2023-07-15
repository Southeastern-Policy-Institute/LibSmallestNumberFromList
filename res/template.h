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
#   include <util/universal_header.h>
#   ifdef __cplusplus
namespace snfl {

  /* C++ exclusive code here */

  extern "C" {
#   endif /* __cplusplus */

    /* C compatible function calls go here */

    /* An example of how to properly declare a public-facing function:
    * LIBSPEC LINKAGE unsigned int rpg_RNG (void);
    * This is for Windows DLL compatibility.
    */

#   include <util/universal_footer.h>
#   ifdef __cplusplus
  };
};
#   endif /* __cplusplus */
# endif /* _SMALLESTNUMBERFROMLIST_FILENAME_H_ */
