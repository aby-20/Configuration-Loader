#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include"config.h"

char* load_file(const char* path ,size_t *out_size){

int fd = open(path,O_RDONLY);
if (out_size) *out_size = 0;

if(fd == -1){

return NULL;
}

struct stat st;
int check;
check = fstat(fd,&st);
if(check==-1){
close(fd);
return NULL;
}

char *buff = malloc(st.st_size+1);

if (buff == NULL){
close(fd);
return NULL;
}
size_t file_size = st.st_size;
size_t bytes_read = 0;

while(bytes_read<file_size){
ssize_t n = read(fd,buff+bytes_read,file_size-bytes_read);
if(n>0){
bytes_read+=n;
}
else if(n==0){
break;
}
else if(n==-1){
if(errno == EINTR){
continue;
}
free(buff);
close(fd);
return NULL;
}
}
buff[bytes_read] = '\0';
*out_size = bytes_read;
close(fd);
return buff;

}
