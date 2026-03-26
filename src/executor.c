#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "shell.h"

void execute_command(char *tokens[], int token_count, int background)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        handle_redirection(tokens, token_count);
        execvp(tokens[0], tokens);
        perror("exec failed");
        exit(1);
    }
    else if (pid > 0 && !background)
    {
        wait(NULL);
    }
}

void execute_pipeline_commands(char *cmds[][MAX_TOKENS], int cmd_count, int background)
{
    int pipes[MAX_CMDS][2];

    for (int i = 0; i < cmd_count - 1; i++)
        pipe(pipes[i]);

    for (int i = 0; i < cmd_count; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);

            if (i == 0)
                dup2(pipes[i][1], STDOUT_FILENO);
            else if (i == cmd_count - 1)
                dup2(pipes[i - 1][0], STDIN_FILENO);
            else
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                dup2(pipes[i][1], STDOUT_FILENO);
            }

            for (int j = 0; j < cmd_count - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(cmds[i][0], cmds[i]);
            perror("exec failed");
            exit(1);
        }
    }

    for (int i = 0; i < cmd_count - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    if (!background)
        for (int i = 0; i < cmd_count; i++)
            wait(NULL);
}