# Instructions

Read `docs/` first. Treat it as authoritative.

If code and docs disagree, docs are correct.

Stay within the requested scope.
Change only what is necessary.
Do not widen the task.

Preserve architectural boundaries.
Do not move policy into the kernel.
Do not bypass defined interfaces.
Do not introduce ambient authority.

Prefer simple, procedural, readable code.
Use clear top-down control flow.
Use guard clauses.
Avoid cleverness, hidden behavior, and unnecessary abstraction.

Keep behavior deterministic.
Do not add probing, discovery, randomness, or host-dependent behavior.
Do not add background side effects.

Honor existing contracts.
Do not silently change:
- object lifetimes
- ownership rules
- rights or authority flow
- memory ordering assumptions
- public headers
- ABI-visible behavior

Shape before behavior.
If the task is early scaffolding, define surfaces first.
Do not invent full implementations when only contracts are needed.

Keep comments brief and useful.
Explain why, not what.
Do not restate obvious code.

Tests must match the surface changed.
Prefer compile, link, and narrow contract tests before broad behavior tests.

Do not create new top-level directories or new governance files unless explicitly required.

Update authoritative docs when a public contract or architectural rule changes.

Before finishing:
1. Re-check scope.
2. Re-check docs alignment.
3. Re-check for unnecessary changes.
4. Re-check determinism.
5. Re-check tests.
