#ifndef OS_AUTHORITY_H
#define OS_AUTHORITY_H

#include <os/handle.h>
#include <os/handle_table.h>
#include <os/rights.h>

/* Minimal public authority contract vocabulary. */
typedef os_handle_t os_authority_handle_t;
typedef os_handle_table_t os_authority_handle_table_t;
typedef os_rights_t os_authority_rights_t;

/*
 * Object access requires:
 * - a valid handle
 * - resolution within a valid handle table
 * - sufficient rights for the requested operation
 */

#endif /* OS_AUTHORITY_H */
