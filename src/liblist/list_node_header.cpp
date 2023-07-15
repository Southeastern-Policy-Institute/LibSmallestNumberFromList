/*
 *
 */

# ifdef WIN32
#   include <windows.h>
#   define  COMPILING_LIBRPG
#   define  EXPORT __declspec(dllexport) __stdcall
# else
#   define EXPORT
# endif /* WIN32 */
# include <list/list_node_header.h>

namespace snfl {
  namespace __list {
    extern "C" {

      EXPORT __attribute__ ((returns_nonnull))
      list_node_header_ptr_t new_list_node_header (
        list_node_header_ptr_t next,
        list_node_header_ptr_t previous
      ) {
        return new list_node_header_t {next, previous};
      };

      EXPORT __attribute__ ((nonnull))
      void destroy_list_node_header (list_node_header_ptr_t header) {
        delete header;
      };

    };
  };
};