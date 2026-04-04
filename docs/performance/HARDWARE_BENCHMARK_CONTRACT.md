# Hardware Benchmark Contract

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
1. Hardware Microbenchmark Framework
-------------------------------------------------------------------------------

Purpose:

Measure hardware cost independently from software logic.

Requirement:

Hardware measurements must occur before IPC benchmarking.

-------------------------------------------------------------------------------
2. MOV CR3 Benchmark Contract
-------------------------------------------------------------------------------

Measurement scope:

Pipeline serialization
TLB behavior
PCID behavior
Register update

Excluded:

Scheduler logic
IPC routing
Memory allocation

-------------------------------------------------------------------------------
3. Benchmark Environment Requirements
-------------------------------------------------------------------------------

CPU:

Fixed core
Interrupts masked
Invariant TSC verified
Turbo state recorded
SMT state recorded
Virtualization state recorded

Memory:

Pre-faulted
No page faults

System:

No background tasks
Preemption disabled

-------------------------------------------------------------------------------
4. Required Benchmark Test Matrix
-------------------------------------------------------------------------------

Case 1:

Same CR3
Same PCID

Case 2:

Different CR3
Same PCID

Case 3:

Different CR3
Different PCID

Case 4:

Different CR3
INVPCID executed

All cases are mandatory.

-------------------------------------------------------------------------------
5. Cache Sensitivity Benchmark
-------------------------------------------------------------------------------

The system must measure cache-state impact.

Test conditions:

Warm cache
Cold L1
Cold L2
Mixed state

Required:

Median
95th percentile
99th percentile

Acceptance:

Variance must not exceed 30 percent.
