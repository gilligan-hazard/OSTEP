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
        // execvp() searches for an executable if the filename does not contain a slash
        char *file = strdup("ls");
        char *args[2];
        args[0] = file;
        args[1] = NULL;
        execvp(file, args);
    }
    return 0;
}