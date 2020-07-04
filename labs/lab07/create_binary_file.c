#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
int main(int argc, char *argv[]){
    FILE *o_stream = fopen(argv[1], "w");
    int i = 2;
    if (o_stream == NULL){
        perror(argv[1]);
        return 1;
    }
    while (i < argc){
        fputc(atoi(argv[i]), o_stream);
        i++;
        }
    fclose(o_stream);
    return 0;
}
