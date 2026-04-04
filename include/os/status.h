#ifndef OS_STATUS_H
#define OS_STATUS_H

/* Minimal public status contract: success is zero, errors are negative. */
typedef int os_status_t;

enum {
    OS_STATUS_SUCCESS = 0,

    OS_STATUS_INVALID_HANDLE = -1,
    OS_STATUS_WRONG_TYPE = -2,
    OS_STATUS_ACCESS_DENIED = -3,
    OS_STATUS_OBJECT_DEAD = -4,
    OS_STATUS_RIGHTS_INSUFFICIENT = -5,
    OS_STATUS_TRANSFER_FORBIDDEN = -6,
    OS_STATUS_REVOCATION_COMPLETE = -7,
    OS_STATUS_REVOCATION_PENDING = -8,
};

#endif /* OS_STATUS_H */
