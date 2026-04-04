#ifndef KERNEL_OBJECT_AUTHORITY_VALIDATION_H
#define KERNEL_OBJECT_AUTHORITY_VALIDATION_H

#include "kernel/object/authority_validation_contract.h"

#include <stdint.h>

/*
 * Internal authority validation order helper only.
 *
 * This surface provides deterministic validation-stage ordering shape.
 * It does not perform handle lookup, object lookup, or authority enforcement.
 */
typedef uint32_t os_authority_validation_stage_index_t;

const os_authority_validation_stage_t *os_authority_validation_order(void);
os_authority_validation_stage_index_t os_authority_validation_order_count(void);

#endif /* KERNEL_OBJECT_AUTHORITY_VALIDATION_H */
