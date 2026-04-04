#ifndef KERNEL_OBJECT_AUTHORITY_VALIDATION_CONTRACT_H
#define KERNEL_OBJECT_AUTHORITY_VALIDATION_CONTRACT_H

#include <os/status.h>

/*
 * Internal authority validation contract.
 *
 * Mandatory validation order for kernel object operations:
 * 1) handle table ownership
 * 2) handle validity
 * 3) object type compatibility
 * 4) object liveness
 * 5) required rights
 * 6) operation-specific preconditions
 */
typedef unsigned int os_authority_validation_stage_t;

enum {
    OS_AUTHORITY_VALIDATION_STAGE_HANDLE_TABLE_OWNERSHIP = 1u,
    OS_AUTHORITY_VALIDATION_STAGE_HANDLE_VALIDITY = 2u,
    OS_AUTHORITY_VALIDATION_STAGE_OBJECT_TYPE_COMPATIBILITY = 3u,
    OS_AUTHORITY_VALIDATION_STAGE_OBJECT_LIVENESS = 4u,
    OS_AUTHORITY_VALIDATION_STAGE_REQUIRED_RIGHTS = 5u,
    OS_AUTHORITY_VALIDATION_STAGE_OPERATION_PRECONDITIONS = 6u,
};

/*
 * Minimal failure mapping vocabulary from validation stages to public status
 * outcomes.
 */
enum {
    OS_AUTHORITY_VALIDATION_STATUS_HANDLE_TABLE_OWNERSHIP = OS_STATUS_ACCESS_DENIED,
    OS_AUTHORITY_VALIDATION_STATUS_HANDLE_VALIDITY = OS_STATUS_INVALID_HANDLE,
    OS_AUTHORITY_VALIDATION_STATUS_OBJECT_TYPE_COMPATIBILITY = OS_STATUS_WRONG_TYPE,
    OS_AUTHORITY_VALIDATION_STATUS_OBJECT_LIVENESS = OS_STATUS_OBJECT_DEAD,
    OS_AUTHORITY_VALIDATION_STATUS_REQUIRED_RIGHTS = OS_STATUS_RIGHTS_INSUFFICIENT,
    OS_AUTHORITY_VALIDATION_STATUS_OPERATION_PRECONDITIONS = OS_STATUS_ACCESS_DENIED,
};

typedef struct os_authority_validation_stage_status_map {
    os_authority_validation_stage_t stage;
    os_status_t status;
} os_authority_validation_stage_status_map_t;

#endif /* KERNEL_OBJECT_AUTHORITY_VALIDATION_CONTRACT_H */
