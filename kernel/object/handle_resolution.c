#include "kernel/object/handle_resolution.h"

os_handle_resolution_record_t os_handle_resolution_default(void) {
    os_handle_resolution_record_t record = {
        .owning_table = OS_HANDLE_TABLE_INVALID,
        .input_handle = OS_HANDLE_INVALID,
        .handle_generation = (os_generation_t)0u,
        .is_valid = OS_HANDLE_RESOLUTION_INVALID,
        .object_identity =
            {
                .object_id = (os_object_id_t)0u,
                .object_type = (os_object_type_t)0u,
                .object_generation = (os_generation_t)0u,
            },
        .resolved_rights = (os_rights_t)0u,
    };

    return record;
}
