#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s <config>\n", argv[0]);
        return 1;
    }

    cfg_schema schema[] = {
        { "port",  CFG_INT,    1, 0, offsetof(config_t, port)  },
        { "debug", CFG_BOOL,   0, 0, offsetof(config_t, debug) },
        { "host",  CFG_STRING, 1, 0, offsetof(config_t, host)  },
    };

    config_t cfg = {0};

    /* load file */
    size_t size;
    char* buf = load_file(argv[1], &size);
    if (!buf) return 1;

    /* iterate + parse */
    char* cursor = buf;
    char *line, *key, *value;

 while ((line = next_line(&cursor)) != NULL) {

    if (!parse_kv(line, &key, &value))
        continue;

    cfg_schema* entry = find_schema(schema, 3, key);
    if (!entry || entry->seen)
        return 1;

    entry->seen = 1;

    if (!parse_value(entry, value, &cfg))
        return 1;
}

    if (!validate_required(schema, 3))
        return 1;

    printf("port=%d debug=%d host=%s\n",
           cfg.port, cfg.debug, cfg.host);

    free(buf);
    config_destroy(&cfg);
    return 0;
}

