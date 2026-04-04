#include "kernel/object/handle_resolution.h"

int main(void) {
    os_handle_resolution_valid_t valid = OS_HANDLE_RESOLUTION_INVALID;
    os_handle_resolution_record_t record = os_handle_resolution_default();

    os_handle_resolution_record_t refs = {
        .owning_table = record.owning_table,
        .input_handle = record.input_handle,
        .handle_generation = record.handle_generation,
        .is_valid = OS_HANDLE_RESOLUTION_VALID,
        .object_identity = record.object_identity,
        .resolved_rights = record.resolved_rights,
    };

    return (int)(valid + refs.is_valid + refs.handle_generation +
                 refs.object_identity.object_type + refs.resolved_rights);
}
