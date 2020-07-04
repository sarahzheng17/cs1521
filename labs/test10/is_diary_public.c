#define MAX 1000    
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
int main(void){

    struct stat buf;
    char filepath[50];
    char *value = getenv("HOME");
    snprintf(filepath, MAX, "%s/.diary", value);
    if (stat(filepath, &buf) < 0)
    {
    perror("stat error\n");
    return 1;
    }
    if(buf.st_mode & S_IROTH){
        printf("1\n");
    } else{
        printf("0\n");    
    }
    return 0;
}
