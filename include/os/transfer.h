#ifndef OS_TRANSFER_H
#define OS_TRANSFER_H

#include <os/handle.h>
#include <os/handle_table.h>
#include <os/rights.h>

/* Minimal public transfer contract vocabulary. */
typedef os_handle_t os_transfer_handle_t;
typedef os_handle_table_t os_transfer_handle_table_t;
typedef os_rights_t os_transfer_rights_t;
typedef unsigned int os_transfer_mode_t;

enum {
    OS_TRANSFER_MODE_COPY = 1u,
    OS_TRANSFER_MODE_MOVE = 2u,
};

/* Transfer occurs between handle tables and must not widen rights. */

#endif /* OS_TRANSFER_H */
