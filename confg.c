#include<stdio.h>
#include<string.h>

cfg_schema* find_schema(cfg_schema* schema,size_t schema_count ,const char*key){

for(size_t i=0;i<schema_count;i++){
if(strcmp(schema[i].key ,key) == 0)
return &schema[i];
}
return NULL;
}
while (read_next_config_line(fp, &key, &value))   
{
    cfg_schema *entry = find_schema(schema, schema_count, key);

    if (entry == NULL) {
        fprintf(stderr, "Unknown configuration key: %s\n", key);
        return PARSE_ERR_UNKNOWN_KEY;
    }

    if (entry->seen) {
        fprintf(stderr, "Duplicate configuration key: %s\n", key);
        return PARSE_ERR_DUPLICATE_KEY;
    }

    entry->seen = 1;  
}
