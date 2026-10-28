# UNC Compatibility Runtime

A Luau compatibility layer for **owned, local runtimes and test harnesses**.

## Scope

Implement and test documented utility APIs against a pinned Luau build. Platform-specific behavior is provided through explicit host interfaces so the same API can run in a local harness without depending on a live game client.

This project does not include Roblox-client injection, anti-cheat bypasses, protection evasion, or exploit execution against live Roblox experiences.

## Architecture

- `runtime/` — Luau state creation, lifecycle, and host interface.
- `api/` — grouped compatibility modules (debug, filesystem, scripts, instances, metatable, cache, HTTP/WebSocket, Drawing).
- `tests/` — behavior and compatibility tests.
- `docs/` — API support matrix and known differences.

## Implementation rules

1. Every exported function must have a test and a documented support status.
2. Unsupported host-dependent behavior must return a clear error, never a fake success.
3. Filesystem and network access are injected through host interfaces and can be disabled in tests.
4. Keep API groups modular; don't expose a function until its behavior is implemented.

## Status

- [x] Repository initialized
- [ ] Pin Luau version and establish build
- [ ] Add runtime harness and test runner
- [ ] Implement API groups incrementally
- [ ] Publish compatibility matrix

## Build

Build instructions will be added after the Luau dependency and toolchain are pinned.


## Added standalone C++ modules

- `functions/filesystem/filesystem.h/.cpp` — workspace-root-confined file and directory operations.
- `functions/console/Console.h/.cpp` — host-agnostic log levels routed to a host-provided sink; no UI is included.

These modules require C++17 or newer. Each module is standalone and can be added to a host build individually.
