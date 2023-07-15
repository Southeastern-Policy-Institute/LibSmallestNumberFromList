/* LIST_NODE_HEADER.H - Basic internal structure for list headers
 * Claudia Miller
 * Southeastern Policy Institute, 2023
 */

# ifndef _SMALLESTNUMBERFROMLIST_LIST_NODE_HEADER_H_
#   define _SMALLESTNUMBERFROMLIST_LIST_NODE_HEADER_H_
#   if _MSC_VER > 1000
#     pragma once
#   endif /* _MSC_VER */
#   include <stdint-gcc.h>
#   include <util/universal_header.h>
#   ifdef __cplusplus
namespace snfl _GLIBCXX_VISIBILITY (default) {
  namespace __list {
    extern "C" {
#   endif /* __cplusplus */
  
      /* Universal List Node Header */
      typedef struct LIST_NODE_HEADER {
        LIST_NODE_HEADER* _next;
        LIST_NODE_HEADER* _prev;
      } __attribute__ ((packed)) list_node_header_t;
      typedef list_node_header_t* list_node_header_ptr_t;

      /* Generate new list node header
       * VB6 Declaration:
Public Declare Function CreateListNodeHeader _
  Lib "SmallestNumberFromList.dll" Alias "new_list_node_header" _
  (ByVal NextNode As UInteger, ByVal PriorNode As UInteger) as UInteger
       */
      LIBSPEC LINKAGE __attribute__ ((returns_nonnull))
      list_node_header_ptr_t new_list_node_header (
        list_node_header_ptr_t = NULL,
        list_node_header_ptr_t = NULL
      );
      
      /* Destroy list node header
       * VB6 Declaration:
Public Declare Function DestroyListNodeHeader _
  Lib "SmallestNumberFromList.dll" Alias "destroy_list_node_header" _
  (ByVal NodeHeader As UInteger)
       */
      LIBSPEC LINKAGE __attribute__ ((nonnull))
      void destroy_list_node_header (
        list_node_header_ptr_t
      );

#   include <util/universal_footer.h>
#   ifdef __cplusplus
    };
  };
};
#   endif /* __cplusplus */
# endif /* _SMALLESTNUMBERFROMLIST_LIST_NODE_HEADER_H_ */
