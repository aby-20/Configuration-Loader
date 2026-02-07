#include<stdio.h>
#include "config.h"


int validate_required(cfg_schema* schema,size_t schema_count){
for(size_t i=0 ; i<schema_count;i++){
if(schema[i].required ==1 && schema[i].seen == 0)
{
return 0;
}
}
return 1;
}
