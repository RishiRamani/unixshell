#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

void handle_redirection(char *tokens[], int token_count)
{
    for (int i = 0; i < token_count; i++)
    {
        if (strcmp(tokens[i], ">") == 0)
        {
            int fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (strcmp(tokens[i], ">>") == 0)
        {
            int fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else if (strcmp(tokens[i], "<") == 0)
        {
            int fd = open(tokens[i + 1], O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    }
}