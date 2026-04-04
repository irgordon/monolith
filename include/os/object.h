#ifndef OS_OBJECT_H
#define OS_OBJECT_H

#include <os/types.h>

/* Minimal public object identity contract surface. */
enum {
    OS_OBJECT_TYPE_PROCESS = 1,
    OS_OBJECT_TYPE_THREAD = 2,
    OS_OBJECT_TYPE_ADDRESS_SPACE = 3,
    OS_OBJECT_TYPE_HANDLE_TABLE = 4,
    OS_OBJECT_TYPE_IPC_ENDPOINT = 5,
    OS_OBJECT_TYPE_IPC_CHANNEL = 6,
    OS_OBJECT_TYPE_INTERRUPT_SOURCE = 7,
    OS_OBJECT_TYPE_IOMMU_DOMAIN = 8,
    OS_OBJECT_TYPE_DEVICE_OBJECT = 9,
    OS_OBJECT_TYPE_PFN_SET = 10,
    OS_OBJECT_TYPE_TIMER = 11,
    OS_OBJECT_TYPE_SERVER_INSTANCE = 12,
};

typedef struct os_object_identity {
    os_object_id_t object_id;
    os_object_type_t object_type;
    os_generation_t object_generation;
} os_object_identity_t;

#endif /* OS_OBJECT_H */
