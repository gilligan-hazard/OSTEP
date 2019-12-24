#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    char path[] = "./p3.output";
    char child_wr_buf[] = "hello\n";
    char parent_wr_buf[] = "goodbye\n";

    int child_wr_buf_size = strlen(child_wr_buf);
    int parent_wr_buf_size = strlen(parent_wr_buf);

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
        if (write(wr_fd, child_wr_buf, child_wr_buf_size) < 0)
        {
            fprintf(stderr, "[child] failed to write to file\n");
            exit(1);
        }
    }
    else
    {
        // poll file for child process greeting
        char parent_rd_buf[child_wr_buf_size];
        int parent_rd_buf_size = 0;

        int rd_fd = open(path, O_RDONLY);
        if (rd_fd < 0)
        {
            fprintf(stderr, "[parent] failed to open file for reading\n");
            exit(1);
        }

        while (parent_rd_buf_size < child_wr_buf_size)
        {
            parent_rd_buf_size = read(rd_fd, parent_rd_buf, child_wr_buf_size);
            if (parent_rd_buf_size < 0)
            {
                fprintf(stderr, "[parent] failed to read from file\n");
                exit(1);
            }
            if (parent_rd_buf_size == child_wr_buf_size)
            {
                if (write(wr_fd, parent_wr_buf, parent_wr_buf_size) < 0)
                {
                    fprintf(stderr, "[parent] failed to write to file\n");
                    exit(1);
                }
                return 0;
            }
        }
    }
}