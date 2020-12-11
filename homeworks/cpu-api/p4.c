#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        char usage[] = "usage: %s cmd\n" \
        "  cmd: exec() function to run [execl, execle, execlp, execv, execvp, or execvP]\n";
        if (argc < 2)
        {
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
        char *cmd = argv[1];

        if (strcmp(cmd, "execl") == 0)
        {
            char *path = strdup("/bin/ls");
            char *arg0 = path; // one or more pointers to strings; file name first
            char *arg1 = (char *)NULL; // terminated by null pointer
            execl(path, arg0, arg1);
        }

        else if (strcmp(cmd, "execle") == 0)
        {
            char *path = strdup("/bin/ls");
            char *arg0 = path; // one or more pointers to strings; file name first
            char *arg1 = (char *)NULL; // terminated by null pointer
            char *envp[] = {NULL}; // environment of executed process; array of pointers terminated by NULL pointer
            execle(path, arg0, arg1, envp);
        }

        else if (strcmp(cmd, "execlp") == 0)
        {
            char *file = strdup("ls"); // searches for executable in PATH if filename does not contain slash
            char *arg0 = file; // one or more pointers to strings; file name first
            char *arg1 = (char *)NULL; // terminated by null pointer
            execlp(file, arg0, arg1);
        }

        else if (strcmp(cmd, "execv") == 0)
        {
            char *path = strdup("/bin/ls");
            char *args[2]; // array of pointers
            args[0] = path; // file name first
            args[1] = NULL; // terminated by null pointer
            execv(path, args);
        }

        else if (strcmp(cmd, "execvp") == 0)
        {
            char *file = strdup("ls"); // searches for executable in PATH if filename does not contain slash
            char *args[2]; // array of pointers
            args[0] = file; // file name first
            args[1] = NULL; // terminated by null pointer
            execvp(file, args);
        }

        // the execvpe() function is a GNU extension; macOS uses execvP()
        else if (strcmp(cmd, "execvP") == 0)
        {
            char *file = strdup("ls"); // searches for executable in searchPath if filename does not contain slash
            char *searchPath = strdup("/bin");
            char *args[2]; // array of pointers
            args[0] = file; // file name first
            args[1] = NULL; // terminated by null pointer
            execvP(file, searchPath, args);
        }

        else
        {
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    }
    return 0;
}