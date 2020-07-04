#include <stdio.h>
#include <unistd.h>
#include <spawn.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    // Signed integer type capable of representing a process ID 
    extern char **environ;
    // Defined as a global variable in Glibc source file 
    // environ is the address of a list of addresses of strings.
    char *date_argv[] = {"/bin/date", "--utc", NULL};
    if (posix_spawn(&pid, "/bin/date", NULL, NULL, date_argv, environ) != 0) {
        perror("spawn");
        return 1;
    }

    int exit_status;
    if (waitpid(pid, &exit_status, 0) == -1) {
        perror("waitpid");
        return 1;
    }

    printf("/bin/date exit status was %d\n", exit_status);
    return 0;
}
