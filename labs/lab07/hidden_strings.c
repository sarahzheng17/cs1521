#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#define BUF_LENGTH 4 
int main(int argc, char *argv[]){
    FILE *o_stream = fopen(argv[1], "r");
    int i = 0;
    int c;
    
    int buffer[BUF_LENGTH] = {};
    if (o_stream == NULL){
        perror(argv[1]);
        return 1;
    }
    /* print sequences of 4 or more consecutive 
       bytes corresponding to printable ASCII 
       characters */ 
    while ((c = fgetc(o_stream)) != EOF){
        if (isprint(c) != 0 ){
            buffer[i] = c;             
            i++;
            if(i == BUF_LENGTH){
                i = 0;
                while(i <= 4){
                    printf("%c", buffer[i]);
                    i++;
                }
            }
        } 
    }
    fclose(o_stream);
    return 0;
}
