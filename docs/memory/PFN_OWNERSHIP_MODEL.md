# Physical Frame Ownership Model — PFN Database

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
1. PFN Database Authority
-------------------------------------------------------------------------------

All physical frames must be tracked in a kernel-owned PFN database.

The PFN database is the single source of truth.

No subsystem may infer state from page tables.

Each PFN must have exactly one record.

-------------------------------------------------------------------------------
2. PFN Record
-------------------------------------------------------------------------------

struct pfn_record {
    atomic_uint64_t state;
}

Atomic State Fields:

Owner domain
Reference count
Flags
DMA domain

-------------------------------------------------------------------------------
3. Ownership States
-------------------------------------------------------------------------------

UNALLOCATED
KERNEL
DRIVER
USER
DEVICE
FIRMWARE_RESERVED

Invariant:

Reference count must be zero before ownership transfer.

-------------------------------------------------------------------------------
4. Permanent Frame Exclusion Rules
-------------------------------------------------------------------------------

Some frames must never be reused.

Permanent exclusion classes:

Page tables
Kernel stacks
Interrupt stacks
Per-CPU structures
Kernel image pages
Descriptor tables
Slab metadata
Security metadata
Boot memory

Flag:

PFN_FLAG_NEVER_REUSABLE

This flag is irreversible.

-------------------------------------------------------------------------------
5. PFN Ownership Transition Model — Lock-Free
-------------------------------------------------------------------------------

PFN ownership transitions must be lock-free.

Mechanism:

atomic_compare_exchange

All state transitions must occur in a single atomic operation.

No partial updates are permitted.

Locks are allowed only for structural operations:

Database resizing
NUMA rebalancing
Memory hotplug
Early boot initialization

Ownership transfers on unrelated PFNs must never block each other.
