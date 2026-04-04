#ifndef KERNEL_OBJECT_HANDLE_TABLE_CONTRACT_H
#define KERNEL_OBJECT_HANDLE_TABLE_CONTRACT_H

#include <os/handle_table.h>
#include <os/types.h>

/*
 * Internal handle table contract only.
 *
 * Handles resolve only within their owning handle table.
 * Stale handle reuse must fail.
 * Table mismatch must fail.
 * This header defines contract only, not lookup behavior.
 */

typedef uint32_t os_handle_table_slot_index_t;

typedef struct os_handle_table_slot_contract {
    os_object_id_t object_id;
    os_generation_t handle_generation;
} os_handle_table_slot_contract_t;

typedef struct os_handle_table_contract {
    os_handle_table_t table_id;
    const os_handle_table_slot_contract_t *slots;
    os_handle_table_slot_index_t slot_count;
} os_handle_table_contract_t;

#endif /* KERNEL_OBJECT_HANDLE_TABLE_CONTRACT_H */
