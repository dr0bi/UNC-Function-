# UNC Compatibility Runtime

A modular C++ compatibility layer for **owned, local runtimes and test harnesses**.

## Scope and safety boundary

This repository provides utility APIs and host interfaces for local software you control. It does **not** implement Roblox-client injection, anti-cheat bypass, protection evasion, or exploit execution against live Roblox experiences. Functions that depend on Roblox internals are not falsely reported as implemented.

## Modules

Every implemented module is split into a header and source file.

| Module | Status | Notes |
|---|---|---|
| `filesystem` | Implemented, not yet verified by CI | Operations confined to a configured workspace root |
| `console` | Implemented, not yet verified by CI | Host-provided logging sink; no UI |
| `crypt` | Partial | Base64 encode/decode only; not encryption |
| `cache` | Implemented, not yet verified by CI | Thread-safe local string key/value cache |
| `misc` | Partial | Portable string helpers |
| `drawing` | Host interface | Drawing primitives are forwarded to a host-provided canvas |
| `websocket` | Host interface | Transport is injected by the host; this repository does not ship a network backend |
| `input` | Host interface | Queries are supplied by the host |

## Not implemented

The following categories require a compatible runtime/engine adapter and are not implemented by these standalone modules: Roblox Instances and services, Luau script execution/bytecode access, debug introspection and mutation, metatable/function hooking, garbage-collector inspection, thread-identity manipulation, exploit-specific environment/closure functions, and anti-cheat/protection bypasses.

## Build and test

Requires CMake 3.16+ and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

The test target currently covers cache operations, string helpers, and Base64 round-tripping/malformed input. The repository has not yet run CI, so a green build/test result is not claimed.

## Implementation rules

1. Export only behavior that is implemented and documented.
2. Host-dependent behavior must use explicit interfaces and report unavailable behavior honestly.
3. File and network access should be constrained by the host and test configuration.
4. Add tests for each API before marking it verified.
