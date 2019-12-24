#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open("./p2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    if (fd < 0)
    {
        fprintf(stderr, "failed to open file\n");
        exit(1);
    }

    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        char child_buf[] = "hello\n";
        if (write(fd, child_buf, strlen(child_buf)) < 0)
        {
            fprintf(stderr, "[child] failed to write to file\n");
            exit(1);
        }
    }
    else
    {
        char parent_buf[] = "goodbye\n";
        if (write(fd, parent_buf, strlen(parent_buf)) < 0)
        {
            fprintf(stderr, "[parent] failed to write to file\n");
            exit(1);
        }
    }
    return 0;
}