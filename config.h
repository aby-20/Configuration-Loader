#ifndef CONFIG_H
#define CONFIG_H

#include <stddef.h>

/* value types */
typedef enum {
    CFG_INT,
    CFG_BOOL,
    CFG_STRING
} cfg_type;

/* schema entry */
typedef struct {
    const char* key;
    cfg_type type;
    int required;
    int seen;
    size_t offset;
} cfg_schema;

/* final typed config */
typedef struct {
    int port;
    int debug;
    char* host;
} config_t;

/* STEP 1 */
char* load_file(const char* path, size_t* out_size);

/* STEP 2 */
char* next_line(char** cursor);

/* STEP 3 */
int parse_kv(char* line, char** key, char** value);

/* STEP 5 */
cfg_schema* find_schema(cfg_schema* schema, size_t count, const char* key);

/* STEP 6 + 7 */
int parse_value(cfg_schema* entry, const char* value, config_t* out_cfg);

/* STEP 8 */
int validate_required(cfg_schema* schema, size_t count);

/* cleanup */
void config_destroy(config_t* cfg);

#endif /* CONFIG_H */

