#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // create a pipe
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("failed to create pipe");
        exit(1);
    }

    // create child1
    int rc1 = fork();
    if (rc1 < 0)
    {
        perror("[child1] fork failed");
        exit(1);
    }

    // child1: write end of the pipe -> standard output
    if (rc1 == 0)
    {
        // close standard output
        close(STDOUT_FILENO);
        
        // duplicate the write end of the pipe onto the lowest-numbered unused
        // file descriptor - now standard output
        if (dup(fd[1]) < 0)
        {
            perror("[child1] dup failed for pipe's write end");
            exit(1);
        }

        // close read end in child1
        close(fd[0]);
        
        execlp("grep", "grep", "pipe", "-o", "p8.c", (char *)NULL);
    }

    else
    {
        // create child2
        int rc2 = fork();
        if (rc2 < 0)
        {
            perror("[child2] fork failed");
            exit(1);
        }

        // child2: read end of the pipe -> standard input
        else if (rc2 == 0)
        {
            // cllose standard input
            close(STDIN_FILENO);

            // duplicate the read end of the pipe onto the lowest-numbered unused
            // file descriptor - now standard input
            if (dup(fd[0]) < 0)
            {
                perror("[child2] dup failed for pipe's read end");
                exit(1);
            }

            // close write end in child2
            close(fd[1]);

            execlp("wc", "wc", "-l", (char *)NULL);
        }

        else
        {
            // close both ends of the pipe in parent
            close(fd[0]);
            close(fd[1]);
        }
    }

    return 0;
}