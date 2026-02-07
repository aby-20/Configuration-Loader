#include<stdio.h>
#include<errno.h>
#include<limits.h>
#include<ctype.h>


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


