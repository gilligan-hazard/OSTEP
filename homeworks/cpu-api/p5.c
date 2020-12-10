#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        // wait() returns ECHILD error if used in child
        printf("[child] pid: %d\n", (int)getpid());
    }
    else
    {
        // wait() returns the process ID of the terminated child
        int wc = wait(NULL);
        if (wc < 0)
        {
            fprintf(stderr, "wait failed\n");
            exit(1);
        }
        printf("[parent] pid of terminated child: %d\n", wc);
    }
    return 0;
}