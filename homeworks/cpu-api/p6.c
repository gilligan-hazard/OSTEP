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
        printf("[child] pid: %d\n", (int)getpid());
    }
    else
    {
        // waitpid() would be useful to wait for a specific child or a state change other than termination
        printf("[parent] waiting for child with pid %d\n", rc);
        int wc = waitpid(rc, NULL, 0);
        if (wc < 0)
        {
            fprintf(stderr, "wait failed\n");
            exit(1);
        }
        printf("[parent] pid of terminated child: %d\n", wc);
    }
    return 0;
}