#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");
    int i = 0, j = 0;
    int c, k;
    while((c = fgetc(fp1)) != EOF && (k = fgetc(fp2)) != EOF){
        if (k != c){
            printf("Files differ at byte %d\n", i); 
            return 0;              
        } 
    i++;
    j++;
    }
    if (i > j){
        printf("EOF on %s\n", argv[2]);
    } 
    else if(j > i){
        printf("EOF on %s\n", argv[1]);    
    } else {
        printf("Files are identical\n");
    }
    fclose(fp1);
    fclose(fp2);
return 0;
}
