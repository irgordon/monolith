CHANGELOG

Notable repository changes are tracked in this file.

## [v0.0.1]
- Established kernel-internal contract surfaces for authority validation, handle table, and object lifetime.
- Added a minimal internal authority validation helper surface for deterministic validation-order shape.
- Added CI compile-shape enforcement via `.github/workflows/ci.yml`.
- Continued structure-first pre-alpha development with no production runtime behavior.
- Added kernel/object/handle_resolution.h
- Added kernel/object/handle_resolution.c
- Added tests/compile/handle_resolution_header_compile.c
- Introduced a minimal internal handle-resolution helper surface for deterministic resolved-handle record shape only; no full authority enforcement, lookup, type checks, liveness checks, rights enforcement, transfer, revocation, or mutation behavior is implemented.

v0.0.0
- Added .github/workflows/ci.yml for initial CI scaffolding on push and pull_request.
- CI compiles all tests/compile/*_compile.c files using `cc -Iinclude -I. -c` as compile-shape validation.
- Added include/os/status.h
- Added include/os/types.h
- Added include/os/compiler.h
- Added include/os/object.h
- Added include/os/rights.h
- Added include/os/handle.h
- Added include/os/handle_table.h
- Added tests/compile/status_header_compile.c
- Added tests/compile/types_header_compile.c
- Added tests/compile/compiler_header_compile.c
- Added tests/compile/object_header_compile.c
- Added tests/compile/rights_header_compile.c
- Added tests/compile/handle_header_compile.c
- Added tests/compile/handle_table_header_compile.c
- Added include/os/authority.h
- Added tests/compile/authority_header_compile.c
- All changes are structure-only, including the minimal handle table contract surface.
- All authority-surface changes are structure-only and introduce no runtime behavior.
- No runtime behavior implemented.
- Added include/os/transfer.h
- Added tests/compile/transfer_header_compile.c
- Transfer contract additions are structure-only and introduce no runtime behavior.

- Added include/os/revocation.h
- Added tests/compile/revocation_header_compile.c
- Revocation contract additions are structure-only and introduce no runtime behavior.

- Added kernel/object/authority_validation_contract.h
- Added tests/compile/authority_validation_contract_compile.c
- Internal authority validation contract additions are structure-only and introduce no runtime behavior.
- Added kernel/object/handle_table_contract.h
- Added tests/compile/handle_table_contract_compile.c
- Internal handle table contract additions are structure-only and introduce no runtime behavior.
- Added kernel/object/object_lifetime_contract.h
- Added tests/compile/object_lifetime_contract_compile.c
- Internal object lifetime contract additions are structure-only and introduce no runtime behavior.
- Added kernel/object/authority_validation.h
- Added kernel/object/authority_validation.c
- Added tests/compile/authority_validation_header_compile.c
- Introduced a minimal internal helper surface for deterministic authority validation-order shape only; no lookup, rights enforcement, mutation, or full authority validation behavior is implemented.
