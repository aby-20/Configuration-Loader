#include<stdio.h>
#include<string.h>

cfg_schema* find_schema(cfg_schema* schema,size_t schema_count ,const char*key){

for(size_t i=0;i<schema_count;i++){
if(strcmp(schema[i].key ,key) == 0)
return &schema[i];
}
return NULL;
}
