#include<stdio.h>
#include<errno.h>
#include<limits.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>


typedef struct {
    int   port;
    int   debug;
    char* host;   // owned heap string
} config_t;


int parse_int(const char* value,int* out){
if(value==NULL)
return 0;
if(out == NULL)
return 0;
char *endptr;

errno = 0;
long val;
val = strtol(value,&endptr,10);

if(value == endptr)
return 0;
if(errno==ERANGE){
return 0;
}

while(isspace((unsigned char)*endptr)){
endptr++;
}


if(*endptr != '\0')
return 0;

if(val<INT_MIN||val>INT_MAX)
return 0;

*out = (int)val;
return 1;

}

int parse_bool(const char* value,int *out){

if (value == NULL) return 0;
if (out == NULL) return 0;



if(strcmp(value,"true")==0){
*out = 1;
return 1;}
else if(strcmp(value,"false") == 0){
*out = 0;
return 1;}
else if(strcmp(value,"1") == 0){
*out = 1;
return 1;}
else if(strcmp(value,"0") == 0){
*out = 0;
return 1;}

return 0;

}

int parse_string(const char* value,char** out){
if(value==NULL)
return 0;
if(out == NULL)
return 0;

size_t len = strlen(value) +1;
char *copy = malloc(len);
if(copy == NULL)
return 0;
strcpy(copy,value);
*out =copy;
return 1;
//this function assumes the caller must free the memory allocated using the free(*out)

}

int parse_value(cfg_schema* entry,const char* value,config_t* out_cfg){
if (entry == NULL) return 0;
if (value == NULL) return 0;
if (out_cfg == NULL) return 0;

switch (entry->type) {
case CFG_INT:{
int* field = (int*)((char*)out_cfg + entry->offset);
if(!parse_int(value,field))
return 0;
break;}
case CFG_BOOL:{
int* field = (int*)((char*)out_cfg + entry->offset);
if (!parse_bool(value, field))
    return 0;
break;
}
case CFG_STRING:{
char** field = (char**)((char*)out_cfg + entry->offset);
if (!parse_string(value, field))
    return 0;
break;
}
default:
return 0;
}
return 1;


}





