#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    // open file, p2.output
    int fd = open("./p2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd < 0)
    {
        fprintf(stderr, "failed to open file\n");
        exit(1);
    }

    // create a child process
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // write p2.output from the child process
        char child_msg[] = "hello\n";
        if (write(fd, child_msg, strlen(child_msg)) < 0)
        {
            fprintf(stderr, "[child] failed to write to file\n");
            exit(1);
        }
    }
    else
    {
        // write p2.output from the parent process
        char parent_msg[] = "goodbye\n";
        if (write(fd, parent_msg, strlen(parent_msg)) < 0)
        {
            fprintf(stderr, "[parent] failed to write to file\n");
            exit(1);
        }
    }
    return 0;
}