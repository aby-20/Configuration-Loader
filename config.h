#ifndef CONFIG_H
#define CONFIG_H

#include<stddef.h>

typedef enum{
CFG_INT,
CFG_BOOL,
CFG_STRING
}cfg_type;

typedef struct{
const char* key;
cfg_type type;
int required;
int seen;
size_t offset;
}cfg_schema;

typedef struct {
int port,
int debug,
char* host;
}config_t;

char* load_file(const char* path,size_t* out_size);
char* next_line(char**cursor);
int parse_kv(char * line,char**key,char**value);
cfg_schema * find_schema(cfg_schema* schema,size_t count ,const char* key):
int parse_value(cfg_schema* entry, const char* value, config_t* out_cfg);

int validate_required(cfg_schema* schema, size_t count);
void config_destroy(config_t* cfg);

#endif
