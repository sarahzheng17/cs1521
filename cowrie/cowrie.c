// cowrie.c a simple shell


// PUT YOUR HEADER COMMENT HERE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


// PUT EXTRA `#include'S HERE
#include <spawn.h>
#include <limits.h>

#define MAX_LINE_CHARS 1024
#define INTERACTIVE_PROMPT "cowrie> "
#define DEFAULT_PATH "/bin:/usr/bin"
#define WORD_SEPARATORS " \t\r\n"
#define DEFAULT_HISTORY_SHOWN 10

// These characters are always returned as single words
#define SPECIAL_CHARS "!><|"


// PUT EXTRA `#define'S HERE


static void execute_command(char **words, char **path, char **environment);
static void do_exit(char **words);
static int is_executable(char *pathname);
static char **tokenize(char *s, char *separators, char *special_chars);
static void free_tokens(char **tokens);


// PUT EXTRA FUNCTION PROTOTYPES HERE
char *fgetsr( char *str, int size, FILE *fp );

void backwards(char *first);

int main(void) {
    //ensure stdout is line-buffered during autotesting
    setlinebuf(stdout);

    // Environment variables are pointed to by `environ', an array of
    // strings terminated by a NULL value -- something like:
    //     { "VAR1=value", "VAR2=value", NULL }
    extern char **environ;

    // grab the `PATH' environment variable;
    // if it isn't set, use the default path defined above
    char *pathp;
    if ((pathp = getenv("PATH")) == NULL) {
        pathp = DEFAULT_PATH;
    }
    char **path = tokenize(pathp, ":", "");

    char *prompt = NULL;
    // if stdout is a terminal, print a prompt before reading a line of input
    if (isatty(1)) {
        prompt = INTERACTIVE_PROMPT;
    }

    // main loop: print prompt, read line, execute command
    while (1) {
        if (prompt) {
            fputs(prompt, stdout);
        }

        char line[MAX_LINE_CHARS];
        if (fgets(line, MAX_LINE_CHARS, stdin) == NULL) {
            break;
        }

        char **command_words = tokenize(line, WORD_SEPARATORS, SPECIAL_CHARS);
        execute_command(command_words, path, environ);
        free_tokens(command_words);

    }

    free_tokens(path);
    return 0;
}


//
// Execute a command, and wait until it finishes. 
//
//  * `words': a NULL-terminated array of words from the input command line
//  * `path': a NULL-terminated array of directories to search in;
//  * `environment': a NULL-terminated array of environment variables.
//
static void execute_command(char **words, char **path, char **environment) {
    assert(words != NULL);
    assert(path != NULL);
    assert(environment != NULL);

    char *program = words[0];
    // Append each command to $HOME/.cowrie_history
    /* char *history[MAX_LINE_CHARS];
    static int history_num = 0; */
    char histpath[MAX_LINE_CHARS];
    char *value = getenv("HOME");
    snprintf(histpath, MAX_LINE_CHARS, "%s/.cowrie_history", value);
    FILE *fp;
    fp = fopen(histpath, "a");

    if (program == NULL) {
        // nothing to do
        return;
    }

    if (strcmp(program, "exit") == 0) {
        fprintf(fp, "exit %s", "\n");

        do_exit(words);
        // do_exit will only return if there is an error
        return;
    }
    // ADD CODE HERE TO IMPLEMENT SUBSET 0;

    // cd instruction 
    char *dir = words[1];   
    char cwd[MAX_LINE_CHARS]; 
    cwd[0] = '\0';
    if (strcmp(program, "cd") == 0) {
        fprintf(fp, "cd %s ", dir);
        fprintf(fp, "%s", "\n");
        if (dir == NULL){
            char *home = getenv("HOME");
            chdir(home);
        } else {   
            if (chdir(dir) < 0){
            fprintf(stderr, "cd: %s: No such file or directory\n", dir);
            }
        } 
    }
    // pwd instruction 
    if (strcmp(program, "pwd") == 0){
        fprintf(fp, "pwd %s ", "\n");
        if (getcwd(cwd, sizeof(cwd)) != NULL){
            printf("current directory is '%s'\n", cwd);
        } 
    }


    // CHANGE CODE BELOW HERE TO IMPLEMENT SUBSET 1
    else if(strcmp(program, "pwd") != 0 && strcmp(program, "cd") != 0){
        int match = 0; 
        //int k = 1;
        if(strcmp(program, "history") != 0){
            if (strrchr(program, '/') == NULL) {
                /*char *arg = words[k];
                while(words != NULL){
                    fprintf(fp, "%s", arg);
                    k++;
                }    */
                fprintf(fp, "%s", program);
                fprintf(fp, "%s", "\n");  
                while(*path != NULL){
                    char command[MAX_LINE_CHARS] = ""; //full pathname to be searched             
                    strcat(command, *path);
                    strcat(command, "/");
                    strcat(command, cwd);
                    strcat(command, program);    
                    if(is_executable(command) == 1){
                        match = 1;
                        pid_t pid;
                        if (posix_spawn(&pid, command, NULL, NULL, words, environment) != 0){
                            perror("spawn");
                        }
                        int stat;
                        if(waitpid(pid, &stat, 0) == -1){
                            perror("waitpid");                           
                        } 
                        if(WIFEXITED(stat)){
                            printf("%s exit status = %d\n",command, WEXITSTATUS(stat));
                        }   
                    }                        
                path++;
                } 
            } else {
                fprintf(fp, "%s", program);
                fprintf(fp, "%s", "\n");
                if(is_executable(program) == 1){
                    match = 1;
                    pid_t pid;
                    if (posix_spawn(&pid, program, NULL, NULL, words, environment) != 0){
                        perror("spawn");
                    }
                    int exit_status;
                    if(waitpid(pid, &exit_status, 0) == -1){
                        perror("waitpid");                           
                    } 
                    printf("%s exit status = %i\n",program, exit_status);
                }                        
            }
        }
        else if (strcmp(program, "history") == 0){
            
            match = 1;
            char *ptr;
            int n = 0, i = 0;
            if(words[1] != NULL){
                n = (int)strtol(words[1], &ptr, 10);
                fprintf(fp, "history %d ", n);
                fprintf(fp, "%s", "\n");
            } else {
                fprintf(fp, "history %s", "\n");
            }
            // Print the file 
            FILE *fp2 = fopen(histpath, "r");
            // Read into an array
            char line[MAX_LINE_CHARS];
           
            if(words[1] != NULL){
                fseek(fp2, 0, SEEK_END);
                while(fgetsr( line, MAX_LINE_CHARS, fp2 ) != NULL && i < n){
                    backwards(line);
                    printf("%d: %s",i, line);
                    i++;                               
                }
            } else {
                while(fgetsr( line, MAX_LINE_CHARS, fp2 ) != NULL && i < 10){
                    backwards(line);
                    printf("%d: %s",i, line);                
                
                    //printf("%d: %s", count - i, history[count-i]);
                    i++;
                }
            }
        fclose(fp2);
        }         
        if (match == 0){
            fprintf(stderr, "%s: command not found\n", program);    
        }         
    }                   
    fclose(fp);
}

// PUT EXTRA FUNCTIONS HERE
char *fgetsr( char *str, int size, FILE *fp ) {
    if( ftell(fp) == 0 ) {
        return NULL;
    }
    int c = 0;
    while (ftell(fp) != 0 && c < size ) {
        fseek(fp, -1, SEEK_CUR);
        str[c] = (char)fgetc(fp);
        if( str[c] == '\n' && c != 0 ) {
            break;
        }
        fseek(fp, -1, SEEK_CUR);
        c++;
    }
    str[c] = '\0';
    return str;
}
void backwards(char *first){
    size_t size = strlen(first);
    char *last = &first[size - 1];
    
    while (first < last){
    
        char temp = first[0];
        first[0] = last[0];
        last[0] = temp;
    
    first++;
    last--;
    } 

}

//
// Implement the `exit' shell built-in, which exits the shell.
//
// Synopsis: exit [exit-status]
// Examples:
//     % exit
//     % exit 1
//
static void do_exit(char **words) {
    int exit_status = 0;

    if (words[1] != NULL) {
        if (words[2] != NULL) {
            fprintf(stderr, "exit: too many arguments\n");
        } else {
            char *endptr;
            exit_status = (int)strtol(words[1], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "exit: %s: numeric argument required\n",
                        words[1]);
            }
        }
    }

    exit(exit_status);
}


//
// Check whether this process can execute a file.
// Use this function when searching through the directories
// in the path for an executable file
//
static int is_executable(char *pathname) {
    struct stat s;
    return
        // does the file exist?
        stat(pathname, &s) == 0 &&
        // is the file a regular file?
        S_ISREG(s.st_mode) &&
        // can we execute it?
        faccessat(AT_FDCWD, pathname, X_OK, AT_EACCESS) == 0;
}


//
// Split a string 's' into pieces by any one of a set of separators.
//
// Returns an array of strings, with the last element being `NULL';
// The array itself, and the strings, are allocated with `malloc(3)';
// the provided `free_token' function can deallocate this.
//
static char **tokenize(char *s, char *separators, char *special_chars) {
    size_t n_tokens = 0;
    // malloc array guaranteed to be big enough
    char **tokens = malloc((strlen(s) + 1) * sizeof *tokens);


    while (*s != '\0') {
        // We are pointing at zero or more of any of the separators.
        // Skip leading instances of the separators.
        s += strspn(s, separators);

        // Now, `s' points at one or more characters we want to keep.
        // The number of non-separator characters is the token length.
        //
        // Trailing separators after the last token mean that, at this
        // point, we are looking at the end of the string, so:
        if (*s == '\0') {
            break;
        }

        size_t token_length = strcspn(s, separators);
        size_t token_length_without_special_chars = strcspn(s, special_chars);
        if (token_length_without_special_chars == 0) {
            token_length_without_special_chars = 1;
        }
        if (token_length_without_special_chars < token_length) {
            token_length = token_length_without_special_chars;
        }
        char *token = strndup(s, token_length);
        assert(token != NULL);
        s += token_length;

        // Add this token.
        tokens[n_tokens] = token;
        n_tokens++;
    }

    tokens[n_tokens] = NULL;
    // shrink array to correct size
    tokens = realloc(tokens, (n_tokens + 1) * sizeof *tokens);

    return tokens;
}


//
// Free an array of strings as returned by `tokenize'.
//
static void free_tokens(char **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}
