# Stack Protection and Guard Model

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
1. Interrupt Stack Guard Pages
-------------------------------------------------------------------------------

All permanent stacks must be protected.

Mandatory layout:

Guard Page
Stack Pages
Guard Page

Guard page properties:

Not present
Never reusable
Kernel-only

Overflow detection:

Guard page fault triggers kernel panic.

-------------------------------------------------------------------------------
2. Stack Safety Invariants
-------------------------------------------------------------------------------

Interrupt stacks must be guarded.
