#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd[2];
    if (pipe(fd) < 0)
    {
        perror("failed to create pipe");
        exit(1);
    }

    int rc1 = fork();
    if (rc1 < 0)
    {
        perror("child1 fork failed");
        exit(1);
    }

    // child1: write end of the pipe -> standard output
    if (rc1 == 0)
    {
        close(STDOUT_FILENO);
        if (dup(fd[1]) < 0)
        {
            perror("[child1] dup failed for pipe's write end");
            exit(1);
        }
        close(fd[0]); // no need for read end

        printf("[child1] pid: %d\n", (int)getpid());
        close(fd[1]);
    }

    else
    {
        int rc2 = fork();
        if (rc2 < 0)
        {
            perror("child2 fork failed");
            exit(1);
        }

        // child2: read end of the pipe -> standard input
        else if (rc2 == 0)
        {
            close(STDIN_FILENO);
            if (dup(fd[0]) < 0)
            {
                perror("[child2] dup failed for pipe's read end");
                exit(1);
            }
            close(fd[1]); // no need for write end

            char c;
            while (read(fd[0], &c, 1) > 0)
            {
                write(STDOUT_FILENO, &c, 1);
            }
            close(fd[0]);
        }

        else
        {
            // no need for either end
            close(fd[0]);
            close(fd[1]);

            // wait for children, for aesthetic reasons
            int wc1 = waitpid(rc1, NULL, 0);
            int wc2 = waitpid(rc2, NULL, 0);
            if (wc1 < 0 || wc2 < 0)
            {
                perror("wait failed");
                exit(1);
            }
        }
    }

    return 0;
}