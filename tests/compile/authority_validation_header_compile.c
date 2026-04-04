#include "kernel/object/authority_validation.h"

int main(void) {
    const os_authority_validation_stage_t *stages = os_authority_validation_order();
    os_authority_validation_stage_index_t count =
        os_authority_validation_order_count();

    return (int)(stages[0] + count);
}
