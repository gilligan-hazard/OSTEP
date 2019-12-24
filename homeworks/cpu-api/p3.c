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

    int wr_fd = open(path, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
    if (wr_fd < 0)
    {
        fprintf(stderr, "failed to open file for writing\n");
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
        if (write(wr_fd, child_msg, child_msg_size) < 0)
        {
            fprintf(stderr, "[child] failed to write to file\n");
            exit(1);
        }
    }
    else
    {
        // poll file for child process greeting
        char buf[child_msg_size];
        int buf_size = 0;

        int rd_fd = open(path, O_RDONLY);
        if (rd_fd < 0)
        {
            fprintf(stderr, "[parent] failed to open file for reading\n");
            exit(1);
        }

        while (buf_size < child_msg_size)
        {
            buf_size = read(rd_fd, buf, child_msg_size);
            if (buf_size < 0)
            {
                fprintf(stderr, "[parent] failed to read from file\n");
                exit(1);
            }
            if (buf_size == child_msg_size)
            {
                if (write(wr_fd, parent_msg, parent_msg_size) < 0)
                {
                    fprintf(stderr, "[parent] failed to write to file\n");
                    exit(1);
                }
                return 0;
            }
        }
    }
}