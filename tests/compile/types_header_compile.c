#include <os/types.h>

int main(void) {
    os_handle_t handle = 0;
    os_object_id_t object_id = 0;
    os_object_type_t object_type = 0;
    os_generation_t generation = 0;
    os_rights_t rights = 0;
    os_domain_t domain = 0;

    return (int)(handle + object_id + object_type + generation + rights + domain);
}
