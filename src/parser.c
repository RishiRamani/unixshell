#include <string.h>
#include <stdio.h>
#include "shell.h"

int tokenize(char *input, char *tokens[])
{
    int count = 0;
    char *token = strtok(input, " \t\r\n");

    while (token != NULL)
    {
        tokens[count++] = token;
        if (count >= MAX_TOKENS)
        {
            fprintf(stderr, "Too many tokens\n");
            break;
        }
        token = strtok(NULL, " \t\r\n");
    }

    tokens[count] = NULL;
    return count;
}

int split_commands(char *tokens[], int token_count, char *cmds[][MAX_TOKENS])
{
    int cmd_index = 0, arg_index = 0;

    for (int i = 0; i < token_count; i++)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            cmds[cmd_index++][arg_index] = NULL;
            arg_index = 0;
        }
        else
        {
            cmds[cmd_index][arg_index++] = tokens[i];
        }
    }

    cmds[cmd_index][arg_index] = NULL;
    return cmd_index + 1;
}