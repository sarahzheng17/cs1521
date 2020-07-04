#include <stdio.h>
#include <string.h>
#include "serve_web_page.h"
#include <unistd.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

// Compile with dcc web_server.c serve_web_page.c -o web_server

// pathname is the pathname component of a URL
// if a corresponding file exists the client is sent
// a 200 header assuming file contains HTML
// followed by the file contents
// if a the file can't be opened
// a 404 header is sent with no body
void serve_web_page(char *pathname, FILE *client_stream) {
    if( access( pathname, R_OK ) == 0 ) {
        // file exists
        fprintf(client_stream, HEADER_200);
        FILE *pFile;
        char c;
        pFile = fopen(pathname, "r");
        if (pFile==NULL){
            printf("Error reading file\n");
            exit (1);
           }
        c = fgetc(pFile); 
        while (c != EOF){ 
            fputc(c, client_stream); 
            c = fgetc(pFile); 
        }            
                 
   fclose (pFile);
   fclose (client_stream);  
        
    } else {
        // file doesn't exist
        fprintf(client_stream, HEADER_404);
    }

}
