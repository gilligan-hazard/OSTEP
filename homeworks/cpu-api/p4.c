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
        char input_err[] = "specify exec() function to run [options: execl, execle, execlp, execv, execvp]\n";
        if (argc < 2)
        {
            fprintf(stderr, "%s", input_err);
            exit(1);
        }

        char *cmd = argv[1];
        printf("exec() function: %s()\n", cmd);

        if (strcmp(cmd, "execl") == 0)
        {
            char *path = strdup("/bin/ls");
            char *arg0 = path;
            char *arg1 = (char *)NULL;
            execl(path, arg0, arg1);
        }

        else if (strcmp(cmd, "execle") == 0)
        {
            char *path = strdup("/bin/ls");
            char *arg0 = path;
            char *arg1 = (char *)NULL;
            char *envp[] = {NULL};
            execle(path, arg0, arg1, envp);
        }

        else if (strcmp(cmd, "execlp") == 0)
        {
            char *file = strdup("ls"); // searches for an executable if the filename does not contain a slash
            char *arg0 = file;
            char *arg1 = (char *)NULL;
            execlp(file, arg0, arg1);
        }

        else if (strcmp(cmd, "execv") == 0)
        {
            char *path = strdup("/bin/ls");
            char *args[2];
            args[0] = path;
            args[1] = NULL;
            execv(path, args);
        }

        else if (strcmp(cmd, "execvp") == 0)
        {
            char *file = strdup("ls"); // searches for an executable if the filename does not contain a slash
            char *args[2];
            args[0] = file;
            args[1] = NULL;
            execvp(file, args);
        }

        else
        {
            fprintf(stderr, "%s", input_err);
            exit(1);
        }
    }
    return 0;
}