# Configuration Loader in C (Schema-Validated)

A minimal configuration loader written in **C**, built as a systems-level exercise in parsing, validation, and memory discipline.

The loader reads a plain-text configuration file and converts it into a **fully typed `struct`**, or fails loudly on invalid input.

This project was developed incrementally on the `experiments` branch.

---

## Design Goals

- Explicit, static schema
- Deterministic parsing
- Strict validation (fail fast)
- No undefined behavior
- Clear memory ownership
- Clean separation of responsibilities

No hidden defaults. No silent fallbacks.

---

## Features

- Plain text config file (`key = value`)
- Static schema defining:
  - allowed keys
  - required vs optional fields
  - value types
- Rejects:
  - unknown keys
  - duplicate keys
  - missing required keys
  - invalid values
- Type-safe output:
  - `int`
  - `bool`
  - `string` (heap-owned)
- No global state
- No third-party libraries

---

## Configuration Format

Example `config.conf`:

```text
# server configuration
port = 8080
debug = true
host = localhost
