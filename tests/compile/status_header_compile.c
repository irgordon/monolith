#include <os/status.h>

int main(void) {
    os_status_t refs[] = {
        OS_STATUS_SUCCESS,
        OS_STATUS_INVALID_HANDLE,
        OS_STATUS_WRONG_TYPE,
        OS_STATUS_ACCESS_DENIED,
        OS_STATUS_OBJECT_DEAD,
        OS_STATUS_RIGHTS_INSUFFICIENT,
        OS_STATUS_TRANSFER_FORBIDDEN,
        OS_STATUS_REVOCATION_COMPLETE,
        OS_STATUS_REVOCATION_PENDING,
    };

    return (refs[0] == OS_STATUS_SUCCESS) ? 0 : 1;
}
