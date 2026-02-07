#include "config.h"

char* next_line(char** cursor)
{
    if (!cursor || !*cursor || **cursor == '\0')
        return NULL;

    char* start = *cursor;
    char* scan  = *cursor;

    while (*scan != '\n' && *scan != '\0') {
        scan++;
    }

    if (*scan == '\n') {
        *scan = '\0';          
        *cursor = scan + 1;
    } else {
        *cursor = scan;        // at '\0'
    }

    return start;
}

