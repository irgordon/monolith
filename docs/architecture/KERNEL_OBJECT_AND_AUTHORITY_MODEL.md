# Kernel Object and Authority Model

Version: 1.0 (Canonical)

-------------------------------------------------------------------------------
0. Canonical Authority
-------------------------------------------------------------------------------

This document defines the binding kernel object and authority model.

If implementation and this document disagree, this document is correct.

All invariants in this document are normative.

This document defines mechanism only.

Policy derived from these mechanisms must reside outside the kernel.

-------------------------------------------------------------------------------
1. Purpose
-------------------------------------------------------------------------------

The kernel requires a formal object and authority model to support:

Deterministic ownership
Stable identity
Auditable rights transfer
Bounded revocation
Mechanism-only Ring 0 behavior
Safe interaction between kernel, servers, drivers, and user domains

No kernel service may rely on ambient authority.

All access to kernel-managed resources must flow through explicit authority.

-------------------------------------------------------------------------------
2. Core Design Rule
-------------------------------------------------------------------------------

The kernel exposes objects.

Access to objects occurs only through handles.

A handle conveys specific rights to exactly one object.

A caller possesses authority only if it possesses a valid handle whose rights
allow the requested operation.

There is no implicit authority based on process identity, thread identity,
execution context, or address space membership alone.

Kernel mechanisms must validate handle identity and requested rights on every
operation.

-------------------------------------------------------------------------------
3. Object Model
-------------------------------------------------------------------------------

A kernel object is a kernel-managed entity with:

Stable object type
Stable lifetime semantics
Stable kernel identity
Explicit destruction rule
Explicit authority surface

Each object must have exactly one canonical type.

Each object must define:

Creation rule
Reference rule
Authority rule
Revocation rule
Destruction preconditions

Kernel objects may reference other kernel objects only through explicit and
documented relationships.

No hidden ownership edge may exist.

-------------------------------------------------------------------------------
4. Minimum Kernel Object Set
-------------------------------------------------------------------------------

The minimum object classes are:

PROCESS
THREAD
ADDRESS_SPACE
HANDLE_TABLE
IPC_ENDPOINT
IPC_CHANNEL
INTERRUPT_SOURCE
IOMMU_DOMAIN
DEVICE_OBJECT
PFN_SET
TIMER
SERVER_INSTANCE

Additional object classes may be introduced only by updating this document and
the relevant subsystem contract.

-------------------------------------------------------------------------------
5. Object Identity
-------------------------------------------------------------------------------

Each object must have a kernel-internal identity.

Identity must be unique among live objects.

Identity must not be directly forgeable by user-space.

Identity must not be reused without reuse protection.

Each live object identity must include:

OBJECT_ID
OBJECT_TYPE
OBJECT_GENERATION

Generation must change before identity reuse.

No stale reference may resolve to a newly created object with a reused identity.

-------------------------------------------------------------------------------
6. Handle Model
-------------------------------------------------------------------------------

A handle is the only user-visible kernel authority token.

A handle is an unforgeable reference to exactly one kernel object.

A handle must resolve through the caller's handle table.

A handle value has no meaning outside the handle table in which it is valid.

A handle must not embed ambient rights not present in kernel state.

A handle resolves to:

Target object identity
Granted rights mask
Handle generation or validity guard
Optional transfer metadata
Optional revocation state

Handle lookup must be deterministic and bounded.

-------------------------------------------------------------------------------
7. Handle Table Ownership
-------------------------------------------------------------------------------

Each authority domain must own exactly one primary handle table.

A process must execute using a handle table.

A thread must act through the handle table of its process unless explicitly
documented otherwise.

Handle tables are kernel objects.

Handle table mutation must be explicit and auditable.

A process must not access handles belonging to another process unless a transfer
operation explicitly created equivalent authority.

-------------------------------------------------------------------------------
8. Rights Model
-------------------------------------------------------------------------------

Rights are explicit, typed, and non-ambient.

Each object class must define its valid rights.

A right may authorize one class of operation only if that operation is named in
the object contract.

The generic right classes are:

VIEW
USE
MAP
SEND
RECEIVE
SIGNAL
MODIFY
TRANSFER
DUPLICATE
REVOKE
DESTROY

Object classes may define narrower right sets.

A caller must possess the precise right required by the operation.

Possession of one right must not imply possession of another unless explicitly
defined.

-------------------------------------------------------------------------------
9. Rights Attenuation Rule
-------------------------------------------------------------------------------

Authority may be reduced during transfer or duplication.

Authority must never increase unless the kernel performs a creation operation
whose contract explicitly permits it.

A duplicated handle must grant rights that are equal to or weaker than the
source handle.

A transferred handle must grant rights that are equal to or weaker than the
source handle unless the source handle is consumed and the transfer operation is
documented as move-only.

No kernel primitive may widen rights silently.

-------------------------------------------------------------------------------
10. Creation Rule
-------------------------------------------------------------------------------

Object creation must occur only through a documented kernel mechanism.

Creation must return a new object and at least one initial handle.

The creating authority must be explicitly defined by the object contract.

Creation must establish:

Object type
Initial ownership domain
Initial rights
Initial reference state
Initial destruction preconditions

Partially created objects must not become externally visible.

Failed creation must leave no externally reachable half-initialized object.

-------------------------------------------------------------------------------
11. Reference and Lifetime Rule
-------------------------------------------------------------------------------

An object remains live while one or more of the following is true:

A kernel subsystem holds an internal reference
A handle table contains a valid handle to the object
A documented in-flight operation holds a transient execution reference

All references must be bounded and auditable.

An object must not be destroyed while a valid reference exists.

An object must not become unreachable while a live reference exists.

Lifetime transitions must be deterministic.

-------------------------------------------------------------------------------
12. Use Validation Rule
-------------------------------------------------------------------------------

Every kernel operation on an object must validate, in order:

Handle table ownership
Handle validity
Object type compatibility
Object liveness
Required rights
Operation-specific preconditions

Validation failure must return a defined error.

The kernel must not partially perform an operation before authority validation
completes.

-------------------------------------------------------------------------------
13. Transfer Rule
-------------------------------------------------------------------------------

Authority transfer is explicit.

A handle may be transferred only if the source handle possesses TRANSFER or an
object-specific equivalent right.

Transfer must identify:

Source handle table
Target handle table
Target rights mask
Transfer mode

Valid transfer modes are:

COPY
MOVE

COPY creates an attenuated or equal-rights handle in the target table and
retains the source handle.

MOVE transfers authority to the target table and invalidates the source handle.

Transfer must be atomic from the perspective of external visibility.

A target process must never observe a partially installed handle.

-------------------------------------------------------------------------------
14. Duplication Rule
-------------------------------------------------------------------------------

Duplication creates a second handle in the same authority domain unless another
target domain is explicitly named.

Duplication requires DUPLICATE or an object-specific equivalent right.

Duplication must not widen rights.

Duplication must preserve target object identity.

Duplication must create a distinct handle table entry.

-------------------------------------------------------------------------------
15. Revocation Model
-------------------------------------------------------------------------------

The kernel must support bounded revocation.

Revocation acts on handles, not on ambient identity.

Revocation may be:

Single-handle revocation
Object-wide revocation within one handle table
Global object-handle revocation across all handle tables

The supported revocation scope for each object class must be documented.

A revoked handle must fail all future operations.

Revocation must not invalidate in-flight operations unless the specific
operation contract states how cancellation occurs.

Revocation completion semantics must be explicit:

SYNCHRONOUS
DEFERRED

If deferred revocation exists, the kernel must define the visibility point at
which further use is forbidden.

-------------------------------------------------------------------------------
16. Generation Safety Rule
-------------------------------------------------------------------------------

Handle and object reuse must be generation-safe.

A stale handle value must never resolve to a new authority target after slot
reuse.

A stale object identity must never validate after object destruction and reuse.

Generation counters must change before reuse.

Generation counters must not wrap during the supported system lifetime.

-------------------------------------------------------------------------------
17. Type Safety Rule
-------------------------------------------------------------------------------

A handle is bound to one object type.

The kernel must reject type-incompatible use.

Cross-type reinterpretation is forbidden unless a documented kernel operation
performs an explicit transformation and returns a new handle.

No subsystem may infer object type from numeric handle value patterns.

-------------------------------------------------------------------------------
18. Authority Domain Rule
-------------------------------------------------------------------------------

The kernel recognizes authority domains as explicit security boundaries.

At minimum, the following domains exist:

KERNEL
SERVER
DRIVER
USER

A domain classification does not itself grant rights.

Domain classification constrains object creation, transfer eligibility, mapping
rules, and isolation rules as defined by subsystem contracts.

No domain may access another domain's resources without an explicit handle path.

-------------------------------------------------------------------------------
19. Address Space and Mapping Authority
-------------------------------------------------------------------------------

Mappings are authority-bearing operations.

A caller may map memory only if it possesses:

A handle to the address space with MAP right
A handle to the source memory object with MAP or equivalent right

Mapping authority must be validated against both target and source objects.

No page-table mutation may occur without explicit mapping authority.

Address-space membership alone does not grant mapping authority.

-------------------------------------------------------------------------------
20. IPC Authority
-------------------------------------------------------------------------------

IPC endpoints and channels are kernel objects.

Send and receive authority must be distinct rights unless explicitly documented
otherwise.

A caller may not send to an endpoint without SEND right.

A caller may not receive from an endpoint without RECEIVE right.

Endpoint creation, connection, transfer, and revocation must follow the general
object and handle rules in this document.

No IPC path may bypass the authority model.

-------------------------------------------------------------------------------
21. Interrupt and Device Authority
-------------------------------------------------------------------------------

Interrupt sources, devices, and IOMMU domains are kernel objects.

Binding a device to an IOMMU domain is an authority-controlled operation.

Binding an interrupt source to a handler or server is an authority-controlled
operation.

No driver or server may claim device or interrupt ownership without an explicit
kernel object handle authorizing that association.

-------------------------------------------------------------------------------
22. PFN and Physical Memory Authority
-------------------------------------------------------------------------------

PFN ownership remains governed by the PFN ownership model.

Direct access to PFN state is not granted by handle possession unless a PFN_SET
or equivalent object class explicitly authorizes such operations.

The object model must not bypass PFN ownership invariants.

No object-rights rule may permit violation of:

Single authoritative PFN record
Atomic ownership transition
Reference count preconditions
Never-reusable frame rules

-------------------------------------------------------------------------------
23. Server Instance Authority
-------------------------------------------------------------------------------

A subsystem server must operate through a SERVER_INSTANCE object or equivalent
documented authority root.

Server restart, liveness monitoring, cancellation, and resource revocation must
act on explicit kernel objects bound to that server instance.

The kernel must not rely on informal process identity alone when supervising
servers.

-------------------------------------------------------------------------------
24. Fault and Destruction Semantics
-------------------------------------------------------------------------------

Object destruction must be explicit or mechanically implied by the final
reference release, as defined by the object contract.

Destruction must occur only when:

No valid handles remain
No kernel references remain
No in-flight operations hold execution references
Object-specific destruction preconditions are satisfied

Destruction must be linearizable from the perspective of external observation.

After destruction, all stale handles must fail.

-------------------------------------------------------------------------------
25. Error Model
-------------------------------------------------------------------------------

Authority-related failures must return defined status codes.

At minimum, the kernel must distinguish:

INVALID_HANDLE
WRONG_TYPE
ACCESS_DENIED
OBJECT_DEAD
RIGHTS_INSUFFICIENT
TRANSFER_FORBIDDEN
REVOCATION_COMPLETE
REVOCATION_PENDING

Subsystem documents may define narrower or additional errors.

Error returns must not leak unauthorized object state.

-------------------------------------------------------------------------------
26. Kernel Invariants
-------------------------------------------------------------------------------

The following invariants are mandatory:

Every externally accessible kernel resource must be represented by an object.

Every externally exercisable authority must flow through a handle.

No ambient authority may authorize kernel object access.

Every handle must resolve within exactly one handle table.

Every object must have stable type and generation-safe identity.

Every operation must validate rights before mutation.

Authority transfer must be explicit and non-widening.

Revocation must produce a defined future-failure point.

Object destruction must not race with successful post-destruction use.

-------------------------------------------------------------------------------
27. Forbidden Patterns
-------------------------------------------------------------------------------

Forbidden:

Ambient authority based on process role alone
Implicit access based on address-space membership alone
Raw pointer authority exposed to user-space
Object type inference from handle bit patterns
Silent rights widening during duplication or transfer
Use of destroyed object identity after reuse
Cross-domain access without explicit handle transfer
Policy decisions encoded as hidden kernel-side authority exceptions

-------------------------------------------------------------------------------
28. Relationship to Other Canonical Documents
-------------------------------------------------------------------------------

This document defines object identity and authority semantics for the entire
kernel.

The following documents depend on this document:

docs/architecture/SYSTEM_ARCHITECTURE.md
docs/memory/PFN_OWNERSHIP_MODEL.md
docs/memory/ADDRESS_SPACE_MODEL.md
docs/device/DMA_ISOLATION_MODEL.md
docs/device/DRIVER_MEMORY_MODEL.md
docs/execution/EXECUTION_AND_IPC_MODEL.md
docs/reliability/FAULT_AND_RECOVERY_MODEL.md
docs/security/STACK_AND_GUARD_MODEL.md

If a subsystem contract grants access to a resource, that access must be
expressed using the object and authority rules in this document.
