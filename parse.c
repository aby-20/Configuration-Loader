#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>

char* trim(char *s){
size_t end = strlen(s);
size_t begin = 0;

//We have now defined the variables for the function
//next we gonna add the trimming function
//let's trim first

while(begin<end && isspace((unsigned char) s[begin]))
begin++;
while(end>begin && isspace((unsigned char) s[end-1]))
end--;
/* 
now we have to put a null terminator at the end of the line */
//ithanu nammude prototype trimmer enthu nadakkum ennu nokkam
//next we have to return the trimmed line so we can use it

s[end] = '\0';
return s+begin;

}

int parse_kv(char *line,char** key,char** value){
line = trim(line);
}



