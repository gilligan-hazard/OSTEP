#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char path[] = "./p3.output";
    char child_msg[] = "hello\n";
    char parent_msg[] = "goodbye\n";

    int child_msg_size = strlen(child_msg);
    int parent_msg_size = strlen(parent_msg);

    int fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
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
        if (write(fd, child_msg, child_msg_size) < 0)
        {
            fprintf(stderr, "[child] failed to write to file\n");
            exit(1);
        }
    }
    else
    {
        int n = 0;
        while (n < child_msg_size)
        {
            n = lseek(fd, 0, SEEK_CUR);
            if (n < 0)
            {
                fprintf(stderr, "[parent] failed to read file offset\n");
                exit(1);
            }
        }

        if (write(fd, parent_msg, parent_msg_size) < 0)
        {
            fprintf(stderr, "[parent] failed to write to file\n");
            exit(1);
        }
        return 0;
    }
}