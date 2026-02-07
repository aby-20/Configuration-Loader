Configuration Loader in C (Schema-Validated)

A minimal configuration loader written in C, built as a systems-level exercise in parsing, validation, and memory discipline.

The loader reads a plain-text configuration file and converts it into a fully typed struct, or fails loudly on invalid input.

This project was developed incrementally on the experiments branch.

Design Goals

Explicit, static schema

Deterministic parsing

Strict validation (fail fast)

No undefined behavior

Clear memory ownership

Clean separation of responsibilities

No hidden defaults.
No silent fallbacks.

Features

Plain text config file (key = value)

Static schema defining:

allowed keys

required vs optional fields

value types

Rejects:

unknown keys

duplicate keys

missing required keys

invalid values

Type-safe output:

int

bool

string (heap-owned)

No global state

No third-party libraries

Configuration Format

Example config.conf:

# server configuration
port = 8080
debug = true
host = localhost

Rules

One key = value per line

Whitespace around = is allowed

Empty lines and comments (#) are ignored

Keys must exist in the schema

Duplicate keys are rejected

Missing required keys cause failure

Schema Definition

The schema is defined statically in code and is the single source of truth:

cfg_schema schema[] = {
    { "port",  CFG_INT,    1, 0, offsetof(config_t, port)  },
    { "debug", CFG_BOOL,   0, 0, offsetof(config_t, debug) },
    { "host",  CFG_STRING, 1, 0, offsetof(config_t, host)  },
};


The schema determines:

which keys are allowed

which keys are required

how values are parsed and stored

Output Structure

After successful parsing and validation:

typedef struct {
    int   port;
    int   debug;
    char* host;   // heap-allocated, owned by config
} config_t;


No raw strings or parsing logic escape the loader.

Build & Run
Compile
gcc -Wall -Wextra -Werror *.c -o config_loader

Run
./config_loader config.conf

Example Output
port=8080 debug=1 host=localhost

Expected Failures (By Design)

The program exits immediately on:

unknown key

duplicate key

missing required key

invalid value (e.g. port = abc)

Failures are intentional and explicit.

Project Structure
.
├── main.c              # glue / driver
├── config.h            # shared declarations
├── file_loader.c       # file → memory
├── next_line.c         # line iteration (in-place)
├── parse.c             # key=value parsing
├── valid.c             # schema lookup
├── parse_value.c       # type validation + assignment
├── required.c          # required key enforcement
└── config.conf         # example configuration


Each source file has a single responsibility.

Non-Goals

No JSON / YAML

No environment variable overrides

No dynamic schemas

No hot reload

No defaults

This is a deliberately minimal core.

Status

Branch: experiments

Architecture: complete

Parsing: strict

Memory: explicit ownership

Tested with invalid inputs

Notes

This project was built as a systems-level learning exercise, with emphasis on:

correct string handling

avoiding undefined behavior

disciplined multi-file C structure

clear validation stages
