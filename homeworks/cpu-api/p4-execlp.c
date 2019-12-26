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
        // execlp() searches for an executable if the filename does not contain a slash
        char *file = strdup("ls");
        char *arg0 = file;
        char *arg1 = (char *)NULL;
        execlp(file, arg0, arg1);
    }
    return 0;
}