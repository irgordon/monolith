# Repository Layout

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
0. Purpose
-------------------------------------------------------------------------------

This document defines the canonical repository structure.

If repository layout and this document disagree, this document is correct.

All top-level directories are normative.

No new top-level directory may be introduced without an explicit update to this
document.

The repository layout exists to preserve:

Deterministic development
Stable architectural boundaries
Auditability
Minimal subsystem coupling
Clear ownership of code and documents

-------------------------------------------------------------------------------
1. Repository Principles
-------------------------------------------------------------------------------

The repository must reflect system architecture.

Directory layout is not cosmetic.

Each top-level directory must correspond to one of the following:

Authoritative design
Kernel implementation
Architecture-specific implementation
User-space subsystem implementation
Validation
Build and tooling support

Code must not be placed according to convenience.

Code must be placed according to ownership and architectural role.

-------------------------------------------------------------------------------
2. Top-Level Layout
-------------------------------------------------------------------------------

The canonical top-level structure is:

/
├── docs/
├── include/
├── kernel/
├── arch/
├── servers/
├── drivers/
├── lib/
├── tests/
├── tools/
├── scripts/
├── build/
├── configs/
├── third_party/
├── Makefile
├── README.md
└── CHANGELOG.md

-------------------------------------------------------------------------------
3. Top-Level Directory Definitions
-------------------------------------------------------------------------------

docs/
    Authoritative architecture, subsystem contracts, standards, and validation
    documents.

include/
    Public kernel and subsystem header surfaces that define stable interfaces.

kernel/
    Architecture-independent Ring 0 implementation.

arch/
    Architecture-specific Ring 0 implementation.

servers/
    Ring 3 subsystem servers implementing policy and compatibility behavior.

drivers/
    Driver code. Kernel-mode drivers, if any exist, must remain narrowly scoped.
    User-space driver components belong under servers/ when implemented as
    subsystem services.

lib/
    Shared internal support code permitted only when it does not violate
    subsystem boundaries.

tests/
    Compile, link, unit, integration, and validation tests.

tools/
    Repository-owned validation tools, schema tools, code generators, and
    audit utilities.

scripts/
    Developer and CI helper scripts. Scripts must not define architecture.

build/
    Build outputs, generated intermediates, and temporary artifacts. This
    directory must be ignorable and non-authoritative.

configs/
    Build configurations, cross files, linker configurations, emulator configs,
    and hardware test configurations.

third_party/
    Vendored external dependencies. This directory is non-authoritative for
    system architecture.

Makefile
    Canonical entry point for deterministic build and validation workflows,
    unless replaced by an explicitly documented build system contract.

README.md
    Project entry document.

CHANGELOG.md
    Canonical change history.

-------------------------------------------------------------------------------
4. Documentation Layout
-------------------------------------------------------------------------------

The docs/ tree is authoritative.

The canonical documentation layout is:

docs/
├── architecture/
├── memory/
├── device/
├── execution/
├── reliability/
├── security/
├── performance/
├── standards/
├── process/
└── REPO_LAYOUT.md

Definitions:

docs/architecture/
    System-wide architecture, kernel authority model, object model, and trust
    boundaries.

docs/memory/
    PFN ownership, address-space semantics, page-table rules, TLB invalidation,
    and related memory contracts.

docs/device/
    DMA isolation, IOMMU rules, donation protocols, driver memory contracts,
    and hardware-facing memory rules.

docs/execution/
    Scheduling, threads, IPC, dispatch, and execution semantics.

docs/reliability/
    Fault handling, watchdog behavior, restart semantics, recovery guarantees,
    and liveness contracts.

docs/security/
    Guard pages, privileged execution safety rules, isolation invariants, and
    security-specific low-level constraints.

docs/performance/
    Benchmark contracts, reproducibility rules, measurement methodology, and
    performance acceptance criteria.

docs/standards/
    Coding standards, naming rules, layout standards, documentation standards,
    and repository governance rules.

docs/process/
    Development process, contribution workflow, review gates, release rules,
    and task discipline.

-------------------------------------------------------------------------------
5. Canonical Documents Expected Under docs/
-------------------------------------------------------------------------------

The following documents are expected to exist as the initial canonical set:

docs/architecture/SYSTEM_ARCHITECTURE.md
docs/memory/PFN_OWNERSHIP_MODEL.md
docs/memory/ADDRESS_SPACE_MODEL.md
docs/device/DMA_ISOLATION_MODEL.md
docs/device/DRIVER_MEMORY_MODEL.md
docs/execution/EXECUTION_AND_IPC_MODEL.md
docs/reliability/FAULT_AND_RECOVERY_MODEL.md
docs/security/STACK_AND_GUARD_MODEL.md
docs/performance/HARDWARE_BENCHMARK_CONTRACT.md
docs/REPO_LAYOUT.md

Additional documents may exist, but they must not weaken or contradict these
canonical files.

-------------------------------------------------------------------------------
6. Public Header Layout
-------------------------------------------------------------------------------

The include/ tree defines exported interfaces.

Canonical form:

include/
└── os/
    ├── types.h
    ├── status.h
    ├── compiler.h
    ├── memory/
    ├── execution/
    ├── ipc/
    ├── device/
    ├── security/
    └── arch/

Rules:

Public headers must contain declarations, constants, types, and contracts.

Public headers must not contain hidden policy logic.

Headers under include/ must be safe to include from tests that verify compile
shape only.

Architecture-neutral headers must not depend on architecture-specific private
headers.

Header names must be stable, descriptive, and subsystem-scoped.

-------------------------------------------------------------------------------
7. Kernel Implementation Layout
-------------------------------------------------------------------------------

The kernel/ tree contains architecture-independent Ring 0 code.

Canonical form:

kernel/
├── init/
├── memory/
├── execution/
├── ipc/
├── interrupt/
├── object/
├── device/
├── reliability/
├── security/
└── debug/

Definitions:

kernel/init/
    Boot-independent early kernel initialization after architecture handoff.

kernel/memory/
    PFN database logic, allocators, virtual memory coordination, mapping logic,
    and ownership transitions.

kernel/execution/
    Thread structures, scheduling logic, run queues, context-independent
    dispatch logic.

kernel/ipc/
    Endpoint handling, message transfer, validation, and IPC routing logic.

kernel/interrupt/
    Interrupt dispatch, interrupt bookkeeping, and architecture-independent
    interrupt coordination.

kernel/object/
    Kernel object lifecycle, handle or capability logic, and identity tracking.

kernel/device/
    Device-facing kernel support, IOMMU coordination, DMA revocation helpers,
    and kernel-side device isolation logic.

kernel/reliability/
    Watchdogs, restart coordination, fault escalation, and liveness mechanisms.

kernel/security/
    Guard-page setup, privileged safety checks, hardening support, and
    security-specific enforcement inside Ring 0.

kernel/debug/
    Diagnostics, tracing hooks, crash reporting surfaces, and debug-only
    support that remains bounded and explicitly optional.

-------------------------------------------------------------------------------
8. Architecture-Specific Layout
-------------------------------------------------------------------------------

The arch/ tree contains implementation that depends on CPU architecture.

Canonical form:

arch/
├── x86_64/
│   ├── include/
│   ├── boot/
│   ├── cpu/
│   ├── mm/
│   ├── interrupt/
│   ├── syscall/
│   └── platform/
└── aarch64/
    ├── include/
    ├── boot/
    ├── cpu/
    ├── mm/
    ├── interrupt/
    ├── syscall/
    └── platform/

Rules:

arch/x86_64/ contains only x86_64-specific code.
arch/aarch64/ contains only AArch64-specific code.

No architecture-specific implementation may leak into kernel/ unless the
boundary is explicitly defined by a public contract.

arch/*/include/ may contain private architecture headers.

Architecture-specific code must remain behind stable interfaces consumed by the
kernel core.

-------------------------------------------------------------------------------
9. Subsystem Server Layout
-------------------------------------------------------------------------------

The servers/ tree contains Ring 3 subsystem servers.

Canonical form:

servers/
├── init/
├── vfs/
├── process/
├── session/
├── net/
├── storage/
├── compatibility/
└── driver_host/

Definitions:

servers/init/
    Initial user-space bootstrap and service launch sequencing.

servers/vfs/
    File-system namespace, file service policy, and storage-facing mediation.

servers/process/
    User-space process policy, loader policy, and related supervisory behavior.

servers/session/
    Session, terminal, console, and interactive policy services.

servers/net/
    Networking subsystem services and protocol policy.

servers/storage/
    Storage management policy outside the minimal kernel mechanism boundary.

servers/compatibility/
    Compatibility personalities or ABI translation servers.

servers/driver_host/
    User-space driver hosting and isolation services when drivers are executed
    outside Ring 0.

Rules:

Policy belongs in servers/.

Servers must consume kernel mechanisms through defined IPC or syscall contracts.

Servers must not bypass kernel authority boundaries.

-------------------------------------------------------------------------------
10. Driver Layout
-------------------------------------------------------------------------------

The drivers/ tree is for device-specific implementations that are not general
kernel mechanisms.

Canonical form:

drivers/
├── bus/
├── block/
├── net/
├── input/
├── gpu/
└── platform/

Rules:

Drivers must not become ad hoc subsystems.

Shared driver support code belongs in a narrowly scoped helper layer only when
that code cannot remain private to a single driver.

DMA rules and memory ownership rules defined in docs/device/ remain binding.

-------------------------------------------------------------------------------
11. Shared Internal Library Layout
-------------------------------------------------------------------------------

The lib/ tree exists only for carefully bounded reuse.

Canonical form:

lib/
├── bitmap/
├── atomics/
├── strings/
├── containers/
└── checks/

Rules:

lib/ is not a dumping ground.

A utility may be placed in lib/ only if:

1. it is used by multiple subsystems,
2. it does not introduce architectural backchannels,
3. it does not hide ownership or authority,
4. it remains deterministic and auditable.

Subsystem-specific helpers must remain inside that subsystem.

-------------------------------------------------------------------------------
12. Test Layout
-------------------------------------------------------------------------------

The tests/ tree mirrors the implementation and contract surfaces.

Canonical form:

tests/
├── compile/
├── link/
├── unit/
├── integration/
├── performance/
├── architecture/
├── memory/
├── device/
├── execution/
├── reliability/
└── security/

Definitions:

tests/compile/
    Compile-only tests validating header shape, type visibility, and contract
    inclusion rules.

tests/link/
    Link-only tests validating symbol presence and surface continuity.

tests/unit/
    Narrow deterministic behavioral tests for isolated components.

tests/integration/
    Cross-subsystem tests validating contract interaction.

tests/performance/
    Benchmark harnesses and performance validation suites.

tests/architecture/
tests/memory/
tests/device/
tests/execution/
tests/reliability/
tests/security/
    Subsystem-aligned test trees for direct traceability to canonical docs.

Rules:

Tests must mirror architectural boundaries.

A test must live near the contract it validates.

Shape tests should exist before complex behavioral tests where feasible.

-------------------------------------------------------------------------------
13. Tooling Layout
-------------------------------------------------------------------------------

The tools/ tree contains repository-owned tooling.

Canonical form:

tools/
├── verify/
├── schema/
├── gen/
└── audit/

Definitions:

tools/verify/
    Deterministic repository validation tools.

tools/schema/
    Machine-readable schemas for authoritative documents or generated metadata.

tools/gen/
    Explicit generators whose outputs are derived and reproducible.

tools/audit/
    Static checks, forbidden-pattern scans, and repository integrity tools.

Rules:

Tools must not silently define architecture.

Generated artifacts must never become authoritative by accident.

-------------------------------------------------------------------------------
14. Script Layout
-------------------------------------------------------------------------------

The scripts/ tree contains supporting automation.

Canonical form:

scripts/
├── ci/
├── dev/
└── release/

Rules:

Scripts may orchestrate workflows.

Scripts must not be the only place where a normative build rule exists.

Normative build and verification behavior must remain documented.

-------------------------------------------------------------------------------
15. Build and Configuration Layout
-------------------------------------------------------------------------------

build/
    Non-authoritative output directory for generated objects, binaries, and
    intermediates.

configs/
    Source-controlled configuration inputs.

Canonical form:

configs/
├── toolchains/
├── link/
├── qemu/
├── hardware/
└── ci/

Definitions:

configs/toolchains/
    Compiler and linker configuration.

configs/link/
    Linker scripts and memory map inputs.

configs/qemu/
    Emulator launch configurations.

configs/hardware/
    Hardware validation and benchmark environment definitions.

configs/ci/
    CI environment configurations.

Rules:

configs/ is authoritative input.

build/ is disposable output.

-------------------------------------------------------------------------------
16. Third-Party Layout
-------------------------------------------------------------------------------

third_party/
    Vendored external code and imported dependencies.

Rules:

External code must remain isolated from first-party architectural boundaries.

Local wrappers around third-party code must live outside third_party/ and must
make the boundary explicit.

No canonical design rule may depend on undocumented third-party behavior.

-------------------------------------------------------------------------------
17. File Placement Rules
-------------------------------------------------------------------------------

Rule 1:
Authoritative design belongs in docs/.

Rule 2:
Public interfaces belong in include/.

Rule 3:
Architecture-neutral kernel code belongs in kernel/.

Rule 4:
Architecture-specific kernel code belongs in arch/<architecture>/.

Rule 5:
User-space policy services belong in servers/.

Rule 6:
Device-specific code belongs in drivers/ unless it is itself a subsystem
server.

Rule 7:
Reusable support code belongs in lib/ only after boundary review.

Rule 8:
Validation belongs in tests/ and tools/.

Rule 9:
Generated outputs must not be committed as authoritative artifacts unless
explicitly documented.

-------------------------------------------------------------------------------
18. Forbidden Layout Patterns
-------------------------------------------------------------------------------

Forbidden:

Placing architecture-specific code directly in kernel/ without a defined
interface boundary

Placing policy code in kernel/

Placing subsystem-private headers under include/

Placing reusable but undocumented helpers in random subsystem directories

Using tests/ as a storage area for reference code or abandoned prototypes

Using scripts/ to hold normative architecture decisions

Using build/ for source-controlled authoritative files

Creating new top-level directories without updating this document

-------------------------------------------------------------------------------
19. Minimal Initial Tree
-------------------------------------------------------------------------------

A minimal initial repository using this layout may begin as:

/
├── docs/
│   ├── architecture/
│   │   └── SYSTEM_ARCHITECTURE.md
│   ├── memory/
│   │   ├── PFN_OWNERSHIP_MODEL.md
│   │   └── ADDRESS_SPACE_MODEL.md
│   ├── device/
│   │   ├── DMA_ISOLATION_MODEL.md
│   │   └── DRIVER_MEMORY_MODEL.md
│   ├── execution/
│   │   └── EXECUTION_AND_IPC_MODEL.md
│   ├── reliability/
│   │   └── FAULT_AND_RECOVERY_MODEL.md
│   ├── security/
│   │   └── STACK_AND_GUARD_MODEL.md
│   ├── performance/
│   │   └── HARDWARE_BENCHMARK_CONTRACT.md
│   └── REPO_LAYOUT.md
├── include/
│   └── os/
├── kernel/
├── arch/
│   ├── x86_64/
│   └── aarch64/
├── servers/
├── drivers/
├── tests/
├── tools/
├── configs/
├── Makefile
├── README.md
└── CHANGELOG.md

-------------------------------------------------------------------------------
20. Evolution Rule
-------------------------------------------------------------------------------

Repository layout may evolve only when one of the following is true:

1. a new architectural boundary is introduced,
2. a prior boundary is split for correctness or auditability,
3. a new execution domain is formally defined,
4. a new hardware support surface requires explicit separation.

All layout evolution must update this document first.

-------------------------------------------------------------------------------
END OF DOCUMENT
-------------------------------------------------------------------------------
