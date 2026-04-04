#include "kernel/object/authority_validation.h"

static const os_authority_validation_stage_t g_authority_validation_order[] = {
    OS_AUTHORITY_VALIDATION_STAGE_HANDLE_TABLE_OWNERSHIP,
    OS_AUTHORITY_VALIDATION_STAGE_HANDLE_VALIDITY,
    OS_AUTHORITY_VALIDATION_STAGE_OBJECT_TYPE_COMPATIBILITY,
    OS_AUTHORITY_VALIDATION_STAGE_OBJECT_LIVENESS,
    OS_AUTHORITY_VALIDATION_STAGE_REQUIRED_RIGHTS,
    OS_AUTHORITY_VALIDATION_STAGE_OPERATION_PRECONDITIONS,
};

const os_authority_validation_stage_t *os_authority_validation_order(void) {
    return g_authority_validation_order;
}

os_authority_validation_stage_index_t os_authority_validation_order_count(void) {
    return (os_authority_validation_stage_index_t)(
        sizeof(g_authority_validation_order) / sizeof(g_authority_validation_order[0]));
}
