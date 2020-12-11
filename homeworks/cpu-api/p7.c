#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // create a child process
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // close standard output
        close(STDOUT_FILENO);

        // printf() fails with EBADF, Bad file descriptor
        printf("gophers in space");
        fprintf(stderr, "print failed: %s\n", strerror(errno));
    }
    return 0;
}