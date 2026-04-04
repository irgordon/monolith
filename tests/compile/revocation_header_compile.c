#include <os/revocation.h>

int main(void) {
    os_revocation_handle_t handle = OS_HANDLE_INVALID;
    os_revocation_handle_table_t table = OS_HANDLE_TABLE_INVALID;
    os_revocation_object_id_t object_id = (os_revocation_object_id_t)1u;
    os_revocation_scope_t scope = OS_REVOCATION_SCOPE_SINGLE_HANDLE;
    os_revocation_completion_t completion = OS_REVOCATION_COMPLETION_SYNCHRONOUS;

    os_revocation_scope_t scopes[] = {
        OS_REVOCATION_SCOPE_SINGLE_HANDLE,
        OS_REVOCATION_SCOPE_OBJECT_IN_TABLE,
        OS_REVOCATION_SCOPE_OBJECT_GLOBAL,
    };

    os_revocation_completion_t completions[] = {
        OS_REVOCATION_COMPLETION_SYNCHRONOUS,
        OS_REVOCATION_COMPLETION_DEFERRED,
    };

    return (int)(handle + table + object_id + scope + completion + scopes[0] + completions[0]);
}
