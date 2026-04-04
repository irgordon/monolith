#ifndef OS_HANDLE_TABLE_H
#define OS_HANDLE_TABLE_H

#include <os/types.h>

/* os_object_id_t is defined by <os/types.h>. */
/* Handle values are meaningful only within the handle table in which they are valid. */
/* A handle table is a distinct kernel-managed authority container. */
typedef os_object_id_t os_handle_table_t;

#define OS_HANDLE_TABLE_INVALID ((os_handle_table_t)0u)

#endif /* OS_HANDLE_TABLE_H */
