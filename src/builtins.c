#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int handle_builtin(char *tokens[], int token_count)
{
    if (strcmp(tokens[0], "exit") == 0)
    {
        printf("Exiting shell.\n");
        exit(0);
    }

    if (strcmp(tokens[0], "cd") == 0)
    {
        if (token_count < 2)
        {
            char *home = getenv("HOME");
            if (home)
                chdir(home);
        }
        else if (chdir(tokens[1]) != 0)
        {
            perror("cd");
        }
        return 1;
    }

    return 0;
}