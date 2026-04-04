#ifndef OS_RIGHTS_H
#define OS_RIGHTS_H

#include <os/types.h>

/* Minimal public generic rights contract surface. */
enum {
    OS_RIGHT_VIEW = (os_rights_t)1u << 0,
    OS_RIGHT_USE = (os_rights_t)1u << 1,
    OS_RIGHT_MAP = (os_rights_t)1u << 2,
    OS_RIGHT_SEND = (os_rights_t)1u << 3,
    OS_RIGHT_RECEIVE = (os_rights_t)1u << 4,
    OS_RIGHT_SIGNAL = (os_rights_t)1u << 5,
    OS_RIGHT_MODIFY = (os_rights_t)1u << 6,
    OS_RIGHT_TRANSFER = (os_rights_t)1u << 7,
    OS_RIGHT_DUPLICATE = (os_rights_t)1u << 8,
    OS_RIGHT_REVOKE = (os_rights_t)1u << 9,
    OS_RIGHT_DESTROY = (os_rights_t)1u << 10,
};

#endif /* OS_RIGHTS_H */
