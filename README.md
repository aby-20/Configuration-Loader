Configuration Loader in C (Schema-Validated)

A minimal, deterministic configuration loader written in C, built from scratch with strict schema validation, type safety, and clear failure modes.

This project was implemented step-by-step with a focus on:

explicit invariants

zero undefined behavior

no hidden defaults

no silent fallbacks

✨ Features

Loads configuration from a plain text file

Strict key = value syntax

Static schema definition

Detects:

unknown keys

duplicate keys

missing required keys

invalid values

Type-safe output (int, bool, string)

No global state

No third-party libraries

📄 Configuration Format
# comments start with #
port = 8080
debug = true
host = localhost

Rules

One key = value per line

Whitespace around = is allowed

Empty lines and comments are ignored

Keys must exist in the schema

Duplicate keys are rejected

Missing required keys are rejected

🧱 Schema Definition

The schema is defined statically in code:

cfg_schema schema[] = {
    { "port",  CFG_INT,    1, 0, offsetof(config_t, port)  },
    { "debug", CFG_BOOL,   0, 0, offsetof(config_t, debug) },
    { "host",  CFG_STRING, 1, 0, offsetof(config_t, host)  },
};


This schema is the single source of truth for:

allowed keys

value types

required vs optional fields

🧾 Output Structure

After successful parsing and validation, the configuration is available as a typed struct:

typedef struct {
    int   port;
    int   debug;
    char* host;
} config_t;


No raw strings are exposed outside the loader.

▶️ Build & Run
Compile
gcc -Wall -Wextra -Werror *.c -o config_loader

Run
./config_loader config.conf

Example Output
port=8080 debug=1 host=localhost

❌ Failure Examples (Expected)
Input Error	Result
Unknown key	Program exits
Duplicate key	Program exits
Missing required key	Program exits
Invalid value (port = abc)	Program exits

Failures are intentional and loud.

🧠 Design Philosophy

Define correctness before parsing

Separate syntax, validation, and assignment

Prefer simple linear scans over clever data structures

Fail early, fail deterministically

No hidden behavior

This project is intentionally small but architected like a real systems component.

📂 Project Structure
.
├── main.c                # glue / driver
├── config.h              # shared declarations
├── file_loader.c         # file → memory
├── next_line.c           # line iteration
├── parse.c               # key=value parsing
├── valid.c               # schema lookup
├── parse_value.c         # type validation + assignment
├── required.c            # required key enforcement
└── config.conf           # example config

🚫 Non-Goals

No JSON / YAML

No environment variable overrides

No dynamic schemas

No hot reload

No defaults

This is a deliberately minimal core.

🏁 Status

✅ Complete
🔒 Stable
🧪 Tested with invalid inputs
🧠 Built for learning systems-level C
