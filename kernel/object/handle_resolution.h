#ifndef KERNEL_OBJECT_HANDLE_RESOLUTION_H
#define KERNEL_OBJECT_HANDLE_RESOLUTION_H

#include "kernel/object/handle_table_contract.h"

#include <os/handle.h>
#include <os/object.h>
#include <os/rights.h>

#include <stdint.h>

/*
 * Internal handle resolution helper shape only.
 *
 * Handles resolve only within their owning handle table.
 * Stale generation reuse must fail.
 * This surface defines canonical resolution-record shape only,
 * not full authority enforcement.
 */
typedef uint32_t os_handle_resolution_valid_t;

enum {
    OS_HANDLE_RESOLUTION_INVALID = 0u,
    OS_HANDLE_RESOLUTION_VALID = 1u,
};

typedef struct os_handle_resolution_record {
    os_handle_table_t owning_table;
    os_handle_t input_handle;
    os_generation_t handle_generation;
    os_handle_resolution_valid_t is_valid;
    os_object_identity_t object_identity;
    os_rights_t resolved_rights;
} os_handle_resolution_record_t;

os_handle_resolution_record_t os_handle_resolution_default(void);

#endif /* KERNEL_OBJECT_HANDLE_RESOLUTION_H */
