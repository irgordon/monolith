#include "kernel/object/handle_table_contract.h"

int main(void) {
    os_handle_table_slot_index_t index = 0u;

    os_handle_table_slot_contract_t slot = {
        .object_id = (os_object_id_t)1u,
        .handle_generation = (os_generation_t)1u,
    };

    os_handle_table_slot_contract_t slots[] = {
        slot,
    };

    os_handle_table_contract_t table = {
        .table_id = (os_handle_table_t)1u,
        .slots = slots,
        .slot_count = (os_handle_table_slot_index_t)1u,
    };

    return (int)(index + table.slot_count + table.slots[0].handle_generation);
}
