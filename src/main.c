#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "shell.h"

int main(void)
{
    char input[1024];
    char *tokens[MAX_TOKENS];
    char *cmds[MAX_CMDS][MAX_TOKENS];

    signal(SIGINT, SIG_IGN);

    while (1)
    {
        int background = 0;

        printf("myshell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nExiting shell.\n");
            break;
        }

        int token_count = tokenize(input, tokens);

        if (token_count == 0)
            continue;

        if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0)
        {
            background = 1;
            tokens[--token_count] = NULL;
        }

        if (handle_builtin(tokens, token_count))
            continue;

        int cmd_count = split_commands(tokens, token_count, cmds);

        if (cmd_count > 1)
            execute_pipeline_commands(cmds, cmd_count, background);
        else
            execute_command(tokens, token_count, background);
    }

    return 0;
}