#ifndef SHELL_H
#define SHELL_H

#define MAX_TOKENS 100
#define MAX_CMDS 10

// parser
int tokenize(char *input, char *tokens[]);
int split_commands(char *tokens[], int token_count, char *cmds[][MAX_TOKENS]);

// builtins
int handle_builtin(char *tokens[], int token_count);

// execution
void execute_command(char *tokens[], int token_count, int background);
void execute_pipeline_commands(char *cmds[][MAX_TOKENS], int cmd_count, int background);

// redirection
void handle_redirection(char *tokens[], int token_count);

#endif