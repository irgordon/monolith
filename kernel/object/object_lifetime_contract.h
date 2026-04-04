#ifndef KERNEL_OBJECT_OBJECT_LIFETIME_CONTRACT_H
#define KERNEL_OBJECT_OBJECT_LIFETIME_CONTRACT_H

/*
 * Internal object lifetime contract only.
 *
 * An object must not be treated as live after destruction.
 * An object must not be destroyed while valid references remain.
 * Stale post-destruction use must fail.
 * This header defines contract only, not lifetime implementation.
 */

typedef unsigned int os_object_lifetime_state_t;

enum {
    OS_OBJECT_LIFETIME_STATE_LIVE = 1u,
    OS_OBJECT_LIFETIME_STATE_DYING = 2u,
    OS_OBJECT_LIFETIME_STATE_DEAD = 3u,
};

typedef struct os_object_lifetime_contract {
    os_object_lifetime_state_t state;
} os_object_lifetime_contract_t;

#endif /* KERNEL_OBJECT_OBJECT_LIFETIME_CONTRACT_H */
