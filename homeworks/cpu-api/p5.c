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
        printf("[child] pid: %d\n", (int)getpid());

        // in the child, wait() returns an error - ECHILD, No child processes
        int wc = wait(NULL);
        if (wc < 0)
        {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            exit(1);
        }
    }
    else
    {
        // in the parent, wait() returns the process ID of the terminated child
        int wc = wait(NULL);
        if (wc < 0)
        {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            exit(1);
        }
        printf("[parent] pid of terminated child: %d\n", wc);
    }
    return 0;
}