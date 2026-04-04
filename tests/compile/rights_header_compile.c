#include <os/rights.h>

int main(void) {
    os_rights_t rights[] = {
        OS_RIGHT_VIEW,
        OS_RIGHT_USE,
        OS_RIGHT_MAP,
        OS_RIGHT_SEND,
        OS_RIGHT_RECEIVE,
        OS_RIGHT_SIGNAL,
        OS_RIGHT_MODIFY,
        OS_RIGHT_TRANSFER,
        OS_RIGHT_DUPLICATE,
        OS_RIGHT_REVOKE,
        OS_RIGHT_DESTROY,
    };

    return (int)rights[0];
}
