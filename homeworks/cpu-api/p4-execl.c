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
        char *path = strdup("/bin/ls");
        char *arg0 = path;
        char *arg1 = (char *)NULL;
        execl(path, arg0, arg1);
    }
    return 0;
}