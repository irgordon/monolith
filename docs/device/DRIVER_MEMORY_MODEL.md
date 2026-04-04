# Driver Memory Model

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
1. Driver Memory Classes
-------------------------------------------------------------------------------

Drivers operate using two memory classes.

Driver-Owned Memory:

Purpose:

Device buffers
Runtime state

Ownership:

DRIVER

Lifecycle:

Driver-controlled

-------------------------------------------------------------------------------
2. Kernel Metadata Memory
-------------------------------------------------------------------------------

Purpose:

Kernel-managed structures

Ownership:

KERNEL

Allocation method:

Secure Donation Protocol

Invariant:

Donated pages become permanently kernel-owned.
