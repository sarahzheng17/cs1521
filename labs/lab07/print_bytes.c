#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
int main(int argc, char *argv[]){
    FILE *o_stream = fopen(argv[1], "r");
    int byte_no = 0;
    int c;
    if (o_stream == NULL){
        perror(argv[1]);
        return 1;
    }
    
    while ((c = fgetc(o_stream)) != EOF){
        printf("byte %4d: %3d 0x%02x", byte_no, c, c);
        
        if(isprint(c) != 0){
        printf(" '%c'", c);
        printf("\n");
        } else {
        printf("\n");
        }
        byte_no ++;
        }
        
    
    fclose(o_stream);
 
    return 0;
}
