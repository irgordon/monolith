#include <os/transfer.h>

int main(void) {
    os_transfer_handle_t handle = OS_HANDLE_INVALID;
    os_transfer_handle_table_t table = OS_HANDLE_TABLE_INVALID;
    os_transfer_rights_t rights = OS_RIGHT_TRANSFER;
    os_transfer_mode_t mode = OS_TRANSFER_MODE_COPY;

    os_transfer_mode_t modes[] = {
        OS_TRANSFER_MODE_COPY,
        OS_TRANSFER_MODE_MOVE,
    };

    return (int)(handle + table + rights + mode + modes[0]);
}
