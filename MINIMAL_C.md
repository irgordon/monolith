MINIMAL_C.md

MONOLITH Kernel Object & Handle Model — Minimal C Layout (v1.0)
Status: Foundational
Scope: Defines the permanent “first brick” of the MONOLITH platform.

---

1. Overview

This document defines the minimal C structures and operations required to implement MONOLITH’s kernel object and handle model. These definitions form the stable substrate for all kernel subsystems, user‑mode APIs, and compatibility layers.

The goals of this model:

• Deterministic lifetime
• Explicit ownership
• Type‑safe handle resolution
• Capability‑based access control
• Predictable, readable, top‑down C code
• No implicit destruction
• No hidden behavior


This is the simplest model that satisfies MONOLITH’s architectural invariants.

---

2. Fundamental Types

typedef uint64_t handle_t;


Handles are opaque 64‑bit values. They are not pointers and carry no embedded metadata.

typedef enum kobject_type {
    KOBJ_INVALID = 0,
    KOBJ_PROCESS,
    KOBJ_THREAD,
    KOBJ_EVENT,
    KOBJ_TIMER,
    KOBJ_IO_CONTEXT,
    KOBJ_SECTION,
    KOBJ_DEVICE,
    /* New types appended only; never reorder */
} kobject_type_t;


Object types are stable identifiers. They never change after creation.

typedef uint32_t kcap_t;

#define KCAP_READ      (1u << 0)
#define KCAP_WRITE     (1u << 1)
#define KCAP_EXECUTE   (1u << 2)
#define KCAP_SIGNAL    (1u << 3)
#define KCAP_WAIT      (1u << 4)
#define KCAP_MANAGE    (1u << 5)


Capabilities define what operations a handle may perform on an object.
Capabilities are checked at lookup time.

---

3. Kernel Object Header

Every kernel object begins with this header.
No inheritance, no macros, no virtual dispatch.

typedef struct kobject_header {
    kobject_type_t type;      /* Immutable after creation */
    uint32_t       flags;     /* Object-specific flags */
    kcap_t         default_caps; /* Caps granted when opened */
    uint32_t       refcount;  /* Atomic reference count */
} kobject_header_t;


Invariants

• type is permanent.
• refcount is incremented/decremented explicitly.
• Destruction occurs only when refcount reaches zero.
• No implicit destruction or hidden ownership transfers.


---

4. Handle Table Structures

Each process owns a handle table.
Handles are indices into this table.

typedef struct handle_entry {
    kobject_header_t *object; /* Pointer to kernel object */
    kcap_t            caps;   /* Capabilities for this handle */
    uint32_t          flags;  /* Reserved */
} handle_entry_t;

typedef struct handle_table {
    handle_entry_t *entries;  /* Dynamic array */
    size_t          capacity; /* Allocated slots */
    size_t          used;     /* Active handles */
} handle_table_t;


Invariants

• A handle always refers to exactly one object.
• A handle never outlives its object.
• Capabilities are fixed at open time.
• Closing a handle is deterministic.


---

5. Core Operations (Signatures)

These operations define the entire handle/object model.
All higher‑level subsystems build on them.

Object Lifetime

void kobject_retain(kobject_header_t *obj);
void kobject_release(kobject_header_t *obj); /* Calls destructor at refcount=0 */


Handle Operations

handle_t handle_open(handle_table_t *table,
                     kobject_header_t *obj,
                     kcap_t caps);

void handle_close(handle_table_t *table,
                  handle_t h);

kobject_header_t *handle_lookup(handle_table_t *table,
                                handle_t h,
                                kobject_type_t expected_type,
                                kcap_t required_caps);


Lookup Rules

handle_lookup must validate:

• Handle index is in range
• Entry is active
• Object type matches expected_type
• Capabilities include required_caps


Failure returns NULL or an error code (implementation‑defined).

---

6. Destruction Model

When kobject_release() decrements the reference count to zero:

1. The object’s destructor is invoked.
2. The object’s memory is freed.
3. No further references may exist.


Destructors are object‑specific and must not block.

---

7. Simplicity Constraints

To preserve long‑term clarity:

• No pointer tagging
• No bit‑encoded handles
• No implicit reference transfers
• No hidden global state
• No macro‑based object systems
• No polymorphic dispatch in the kernel


The model must remain readable by a junior developer in one sitting.

---

8. Stability Rules

This document defines permanent kernel physics.
Future layers must adapt to these rules, not modify them.

• Object header layout is stable
• Handle semantics are stable
• Capability model is stable
• Lookup rules are stable
• Destruction rules are stable


New object types may be added, but the model itself does not change.

---

9. Next Steps

Future documents will build on this foundation:

• Object destructor dispatch
• Handle table growth strategy
• First real object type (event or timer)
• IRQL rules for object operations
• System call interface for user‑mode access


This file remains the canonical reference for the first 