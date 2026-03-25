# MONOLITH Platform Design Charter (v1.1)

Status: Foundational  
Scope: Governs all kernel, subsystem, driver, and platform-level design decisions.  
Tagline: A modern desktop OS built on a disciplined monolithic kernel.

---

## 1. Mission and Vision

MONOLITH is designed to deliver a fast, understandable, and developer-friendly operating system for contemporary hardware.  
It prioritizes immediate responsiveness and structural simplicity, providing a clean substrate for native development while allowing Windows compatibility to exist as a layered subsystem.

The platform must remain readable, teachable, and evolvable.  
Architectural discipline is treated as a first-class requirement, not a performance optimization.

System behavior must remain predictable under concurrency, hardware variability, and subsystem failure.

---

## 2. Core Design Principles

### I. Structural Simplicity

The system must be understandable as a whole.  
Subsystems are organized around clear contracts and minimal abstraction layers.  
Complexity must be explicit, bounded, and justified.

Architectural readability is a permanent requirement.

---

### II. Disciplined Monolithic Architecture

The kernel is monolithic for performance and simplicity but modular in behavior.

- Subsystem boundaries are strict and documented
- Drivers execute in kernel space under defined execution contracts
- Policy resides in user space whenever feasible
- Kernel growth must remain deliberate and auditable

Monolithic structure does not justify uncontrolled expansion.

---

### III. Immediate Responsiveness

User interaction latency is a primary system metric.

Critical responsiveness metrics include:

- Power-on to interactive state
- Application launch latency
- Input-to-display latency
- Wake and resume latency
- I/O completion latency

Performance is defined by perceived fluidity and predictability rather than peak throughput.

---

### IV. Compatibility as a Layer

Windows and legacy compatibility are additive subsystems above the core platform.

Compatibility mechanisms:

- Must not redefine kernel primitives
- Must not introduce hidden architectural dependencies
- Must not constrain future kernel evolution

Compatibility depends on stable primitives rather than historical behavior replication.

---

## 3. Structural Vocabulary (The "Physics")

This section defines permanent system invariants.  
These contracts must remain stable across platform versions.

---

### I. Object and Handle Model

All system resources are represented as Kernel Objects.

Examples:

- Processes
- Threads
- Events
- Timers
- Sections
- Devices
- I/O Contexts

Access is mediated through Handles (`handle_t`).

Object requirements:

- Reference-counted lifetime management
- Explicit ownership semantics
- Deterministic destruction behavior
- Capability-based access validation
- Type-safe handle resolution

Objects must never be implicitly destroyed.

---

### II. Execution and Synchronization (IRQL)

To ensure stability and prevent deadlock, the system enforces strict Interrupt Request Levels.

LEVEL_PASSIVE (0)  
Normal thread execution  
Blocking permitted  
Preemption permitted  

LEVEL_DISPATCH (1)  
Scheduler and deferred work execution  
Blocking forbidden  
Preemption restricted  

LEVEL_INTERRUPT (2)  
Hardware interrupt handlers  
Blocking forbidden  
Preemption disabled  

IRQL invariants:

- Code executing above PASSIVE must not perform blocking operations
- Interrupt handlers must execute within bounded time
- Deferred work mechanisms must exist for long-running tasks
- IRQL transitions must be explicit and auditable

---

### III. Asynchronous I/O Model

The native I/O model is completion-based and non-blocking.

Core principles:

- Submission is non-blocking
- Completion defines visibility of results
- Waiting and result retrieval are separate operations
- Kernel validates requests before execution

---

#### I/O Contexts

I/O Contexts are waitable kernel objects.

Each context owns:

- One Submission Queue
- One Completion Queue

Context behavior:

- Becomes signaled when completion queue is non-empty
- Remains signaled until completions are drained
- Supports concurrent submission from multiple threads
- Supports deterministic shutdown behavior

---

#### Memory Region Descriptor (`mem_region`)

All I/O uses memory region descriptors rather than raw pointers.

Descriptor requirements:

- Base address
- Length
- Access permissions
- Mapping attributes
- Pinning state

Descriptor invariants:

- Must remain valid for the duration of the operation
- Must not be modified while an operation is active
- Must be validated at submission time
- Must support DMA-safe operation

Memory visibility rule:

Data written by hardware or drivers becomes visible to user space only after completion is recorded.

---

## 4. Naming and Readability Standards

Code must be readable from top to bottom without requiring external context.

Naming rules:

Project Prefix  
Reserved for global macros and status codes  
Example: `KERN_OK`

Subsystem Prefix  
Used for public APIs  
Examples:

process_create  
vm_map  
io_submit  

Plain Naming  
Used for struct fields and local static functions

Naming must reduce ambiguity without introducing visual noise.

---

## 5. Implementation Rules

### 1. No Hardware Archaeology

The platform targets contemporary hardware standards:

- UEFI firmware
- ACPI device model
- PCIe interconnect
- NVMe storage
- x64 and ARM64 processors
- Modern interrupt controllers

Legacy hardware compatibility is not a design constraint.

---

### 2. Flat 64-bit Address Space

The system operates exclusively in a flat 64-bit virtual address space.

Disallowed:

- Segmented memory models
- 32-bit kernel assumptions
- Address truncation

---

### 3. Fail-Fast Validation

Subsystems must validate all inputs at trust boundaries.

Failure behavior:

- Errors must be explicit
- Invalid state must not propagate
- Recovery paths must be deterministic
- Undefined behavior is prohibited

---

### 4. Deterministic Boot

The boot path must remain minimal and predictable.

Early initialization includes only:

- Memory management
- Scheduler
- Interrupt handling
- Storage access
- Display output
- Input handling

All other services must initialize after user interaction becomes possible.

---

## 6. System Integrity Constraints

The following invariants must never be violated.

- Kernel primitives remain stable once published
- Blocking operations never occur above PASSIVE level
- Memory ownership is always explicit
- Resource lifetimes are always deterministic
- Namespace resolution is deterministic
- Subsystem failure must not corrupt global state
- All state transitions must be observable

These constraints define the stability boundary of the platform.

---

## 7. Non-Goals

The following objectives are explicitly excluded.

Reproducing NT Internals  
MONOLITH is not an NT clone.

Kernel-Level Emulation  
Compatibility logic does not belong in the core kernel.

Multi-Era API Accumulation  
The platform maintains one primary native API model.

Feature-Driven Architecture  
Subsystems are not added solely to match other operating systems.

Hardware Archaeology  
Obsolete hardware support is not a foundational requirement.

---

Guiding Statement:

MONOLITH is defined by clarity, responsiveness, and architectural discipline.  
We build the substrate first, prove its stability, and layer compatibility only where the foundation is solid.
