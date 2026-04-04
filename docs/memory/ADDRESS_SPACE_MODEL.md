# Address Space and Translation Model

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
1. Global TLB Shootdown Requirement
-------------------------------------------------------------------------------

Local invalidation is insufficient.

Global TLB shootdown must occur when:

Reference count > 1

OR

Mapping exists in shared address space

OR

Mapping exists in global domain

Mechanism:

Inter-Processor Interrupt

Required sequence:

Send IPI
Execute local invalidation
Wait for acknowledgement

Ownership transition must not proceed until completion.

-------------------------------------------------------------------------------
2. PCID Generation Tracking
-------------------------------------------------------------------------------

Each PCID must include a generation number.

Identifier:

PCID_ID
PCID_GENERATION

Reuse rule:

Generation must increment before reuse.

Invalidation rule:

INVPCID must execute before reassignment.

Invariant:

No stale translation may survive reuse.

-------------------------------------------------------------------------------
3. Address Space Safety Invariants
-------------------------------------------------------------------------------

TLB entries must be invalidated on all CPUs before reuse.
