#include "kernel/object/object_lifetime_contract.h"

int main(void) {
    os_object_lifetime_state_t state = OS_OBJECT_LIFETIME_STATE_LIVE;

    os_object_lifetime_state_t states[] = {
        OS_OBJECT_LIFETIME_STATE_LIVE,
        OS_OBJECT_LIFETIME_STATE_DYING,
        OS_OBJECT_LIFETIME_STATE_DEAD,
    };

    os_object_lifetime_contract_t contract = {
        .state = OS_OBJECT_LIFETIME_STATE_DYING,
    };

    return (int)(state + states[0] + contract.state);
}
