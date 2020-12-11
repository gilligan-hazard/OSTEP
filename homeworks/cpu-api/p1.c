#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // set the value of x from the main process
    int x = 100;
    printf("x=%d\n", x);

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // check the value of x in the child process
        printf("[child] x=%d\n", x);

        // change the value of x in the child process
        x = 1;
        printf("[child] x=%d\n", x);
    }
    else
    {
        // change the value of x in the parent process
        x = 10000;
        printf("[parent] x=%d\n", x);
    }
    return 0;
}
