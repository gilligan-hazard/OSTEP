#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // set value of x from main process
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
        // check value of x in child process
        printf("[child] x=%d\n", x);

        // change value of x in child process
        x = 1;
        printf("[child] x=%d\n", x);
    }
    else
    {
        // change value of x in parent process
        x = 10000;
        printf("[parent] x=%d\n", x);
    }
    return 0;
}
