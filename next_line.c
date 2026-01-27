#include<stdio.h>

char* next_line(char** cursor)
{
    if(cursor==NULL || *cursor == NULL){
        return NULL;
    }
    else if (**cursor == '\0')
        return NULL;

    char *start = *cursor;
    char *scan = *cursor;

    while(*scan!='\n' && *scan != '\0'){
        scan = scan+1;
    }
    if(*scan == '\n'){
        *cursor = scan+1;
    }
    else if(*scan=='\0'){
    *cursor = scan;
    }
    return start;
    
    }

