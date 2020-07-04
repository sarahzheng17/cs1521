#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char *argv[]){
    FILE *o_stream = fopen(argv[1], "w");
    
    if (o_stream == NULL){
        perror(argv[1]);
        return 1;
    }
    int start = atoi(argv[2]);
    int end = atoi(argv[3]);
    while (start <= end){
        fprintf(o_stream, "%d\n", start);
        start++;
        }
        fclose(o_stream);
        
    
    return 0;
}
