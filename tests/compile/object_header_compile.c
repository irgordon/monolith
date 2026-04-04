#include <os/object.h>

int main(void) {
    os_object_identity_t identity = {
        .object_id = 0,
        .object_type = OS_OBJECT_TYPE_PROCESS,
        .object_generation = 0,
    };

    os_object_type_t object_types[] = {
        OS_OBJECT_TYPE_PROCESS,
        OS_OBJECT_TYPE_THREAD,
        OS_OBJECT_TYPE_ADDRESS_SPACE,
        OS_OBJECT_TYPE_HANDLE_TABLE,
        OS_OBJECT_TYPE_IPC_ENDPOINT,
        OS_OBJECT_TYPE_IPC_CHANNEL,
        OS_OBJECT_TYPE_INTERRUPT_SOURCE,
        OS_OBJECT_TYPE_IOMMU_DOMAIN,
        OS_OBJECT_TYPE_DEVICE_OBJECT,
        OS_OBJECT_TYPE_PFN_SET,
        OS_OBJECT_TYPE_TIMER,
        OS_OBJECT_TYPE_SERVER_INSTANCE,
    };

    return (int)(identity.object_id + identity.object_type +
                 identity.object_generation + object_types[0]);
}
