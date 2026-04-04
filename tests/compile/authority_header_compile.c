#include <os/authority.h>

int main(void) {
    os_authority_handle_t handle = OS_HANDLE_INVALID;
    os_authority_handle_table_t table = OS_HANDLE_TABLE_INVALID;
    os_authority_rights_t rights = OS_RIGHT_VIEW;

    return (int)(handle + table + rights);
}
