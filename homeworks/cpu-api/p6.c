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

        // in the child, waitpid() returns an error - ECHILD, No child processes
        int wc = waitpid(rc, NULL, 0);
        if (wc < 0)
        {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            exit(1);
        }
    }
    else
    {
        // waitpid() is a general interface to wait for any child process or group of child processes
        // exposes options to wait for more specific behaviors
        // can request resource utilization statistics for the child
        int wc = waitpid(rc, NULL, 0);
        if (wc < 0)
        {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            exit(1);
        }
        printf("[parent] pid of terminated child: %d\n", wc);
    }
    return 0;
}