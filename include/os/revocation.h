#ifndef OS_REVOCATION_H
#define OS_REVOCATION_H

#include <os/handle.h>
#include <os/handle_table.h>
#include <os/types.h>

/* Minimal public revocation contract vocabulary. */
typedef os_handle_t os_revocation_handle_t;
typedef os_handle_table_t os_revocation_handle_table_t;
typedef os_object_id_t os_revocation_object_id_t;
typedef unsigned int os_revocation_scope_t;
typedef unsigned int os_revocation_completion_t;

enum {
    OS_REVOCATION_SCOPE_SINGLE_HANDLE = 1u,
    OS_REVOCATION_SCOPE_OBJECT_IN_TABLE = 2u,
    OS_REVOCATION_SCOPE_OBJECT_GLOBAL = 3u,
};

enum {
    OS_REVOCATION_COMPLETION_SYNCHRONOUS = 1u,
    OS_REVOCATION_COMPLETION_DEFERRED = 2u,
};

/* A revoked handle must fail all future operations. */
/* Deferred revocation must define the visibility point where further use is forbidden. */

#endif /* OS_REVOCATION_H */
