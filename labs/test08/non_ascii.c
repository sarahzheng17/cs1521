#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp = fopen(argv[1], "r");
    int i = 0;
    int c;
    while((c = fgetc(fp)) != EOF){
        if (c >= 128 && c <= 255){
            printf("%s: byte %d is non-ASCII\n", argv[1], i); 
            return 0;              
        } 
    i++;
    }
    printf("%s is all ASCII\n",argv[1]);
    fclose(fp);
return 0;
}
