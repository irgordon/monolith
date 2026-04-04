# DMA Isolation and Secure Donation Protocol

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
1. Secure Donation Protocol — Final Sequence
-------------------------------------------------------------------------------

Purpose:

Allow drivers to provide metadata pages safely.

Donation sequence:

1. Validate PFN ownership state

2. Issue IOMMU_UNMAP(PFN)

3. Wait for hardware invalidation completion

4. Execute full memory barrier

5. Remove CPU mapping

6. Perform global TLB shootdown if required

7. Execute full memory barrier

8. Atomically transition PFN ownership

9. Map frame into kernel metadata region

10. Complete operation

Failure rule:

Ownership must remain unchanged on failure.

-------------------------------------------------------------------------------
2. IOMMU Enforcement Requirements
-------------------------------------------------------------------------------

All DMA devices must operate inside isolated IOMMU domains.

Mandatory:

Dedicated domain per device

Kernel metadata pages must never exist in device domains.

DMA revocation must include hardware confirmation.

Completion mechanisms:

Invalidation Wait Descriptor
Completion register polling
Interrupt completion

Invariant:

DMA reachability must be zero before ownership transfer.
