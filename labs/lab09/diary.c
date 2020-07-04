#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#define MAX 1000

int main(int argc, char *argv[]) {
    char filepath[50]; 
    int i = 1;  
    char *value = getenv("HOME");
    snprintf(filepath, MAX, "%s/.diary", value);
    FILE * fp;
    fp = fopen(filepath, "a");
    while (i < argc){
        fprintf(fp, "%s ", argv[i]);
        i++;
    }
        fprintf(fp, "%s", "\n");
    return 0;
}
