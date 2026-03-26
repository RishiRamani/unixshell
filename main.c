#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


/*
pipe - detect pipe
 fork twice 
 create pipe btw both
 do dup2 to redfine fd
 exec both
*/
//Tokenization
int tokenize(char *input,char *tokens[]);
//Handler
int handle_builtin(char *tokens[],int token_count);
//Redirection Handler
void handle_redirection(char *tokens[],int token_count);
//Execution
void execute_command(char *tokens[],int token_count);
//Pipe Split
int split_commands(char *tokens[],int token_count,char *cmds[][100]);
//Pipeline execution
void execute_pipeline_commands(char *cmds[][100],int cmd_count);

int main(void){
  char input[1024];
  char *tokens[100]; // Array to hold pointers to tokens 
  char *cmds[10][100];

  while(1){

    printf("myshell> ");
    fflush(stdout);
    if(fgets(input, sizeof(input), stdin) == NULL){ // fgets returns NULL if it encounters EOF or an error
      printf("\nExiting shell.\n");
      break;
    }

    // Tokenization
    int token_count = tokenize(input,tokens);

    //Handle empty input
    if(token_count==0){
      continue;
    }
    
    if(handle_builtin(tokens,token_count)){
      continue;
    }
    int cmd_count = split_commands(tokens,token_count,cmds);
    if(cmd_count>1){
      execute_pipeline_commands(cmds,cmd_count);
    }else{
      execute_command(tokens,token_count);
    }
    
    
  }
  return 0;
}

int tokenize(char *input,char *tokens[]){
  int token_count=0; 
  char * token = strtok(input, " \v\f\r\t\n");
  while(token != NULL){
    tokens[token_count++] = token; // Store the token in the array and increment the count
    if(token_count >= 100){ // Prevent overflow of the tokens array
      fprintf(stderr, "Too many tokens, maximum is 100.\n");
      break;
    }
    token = strtok(NULL, " \v\f\r\t\n"); // The Null pointer tells strtok to continue from the previous position
  }
  tokens[token_count] = NULL; // Null-terminate the array of tokens
  return token_count;
}


int handle_builtin(char *tokens[],int token_count){

  // Handles exit
  if(strcmp(tokens[0], "exit") == 0){
    printf("Exiting shell.\n");
    exit(0);
  }

  // Handles cd
  if(strcmp(tokens[0], "cd")==0){
    if(token_count < 2){
      char* home = getenv("HOME");

      if(home == NULL){
        fprintf(stderr, "cd: HOME environment variable not set\n");
      }
      else{
        if(chdir(home) != 0){
          perror("cd");
        }
      }
    }
    else if(token_count > 2){
      fprintf(stderr, "cd: too many arguments\n");
    }else{
      if(chdir(tokens[1]) != 0){
        perror("cd");
      }
    }
    return 1;
  }
  return 0;
}


void handle_redirection(char *tokens[],int token_count){
  //Handles redirection to input , output and append , deletes related tokens for smooth execution forward
  for(int i=0;i<token_count;i++){
    if(strcmp(tokens[i], ">")==0){
      if(tokens[i+1]==NULL){
        printf("Syntax error: missing file\n");
        exit(1);
      }
      int file_desc = open(tokens[i+1], O_WRONLY | O_CREAT | O_TRUNC , 0644);
      if(file_desc < 0){
        perror(tokens[i+1]);
        exit(1);
      }
      dup2(file_desc,STDOUT_FILENO);
      close(file_desc);
      for(int j=i;j<token_count-2;j++){
        tokens[j]=tokens[j+2];
      }
      token_count -= 2;
      tokens[token_count]=NULL;
      i--;
    }else if(strcmp(tokens[i], ">>")==0){
      if(tokens[i+1]==NULL){
        printf("Syntax error: missing file\n");
        exit(1);
      }
      int file_desc = open(tokens[i+1], O_WRONLY | O_CREAT | O_APPEND , 0644);
      if(file_desc < 0){
        perror(tokens[i+1]);
        exit(1);
      }
      dup2(file_desc,STDOUT_FILENO);
      close(file_desc);
      for(int j=i;j<token_count-2;j++){
        tokens[j]=tokens[j+2];
      }
      token_count -= 2;
      tokens[token_count]=NULL;
      i--;
    }
    else if(strcmp(tokens[i], "<")==0){
      if(tokens[i+1]==NULL){
        printf("Syntax error: missing file\n");
        exit(1);
      }
      int file_desc = open(tokens[i+1], O_RDONLY);
      if(file_desc < 0){
        perror(tokens[i+1]);
        exit(1);
      }
      dup2(file_desc,STDIN_FILENO);
      close(file_desc);
      for(int j=i;j<token_count-2;j++){
        tokens[j]=tokens[j+2];
      }
      token_count -= 2;
      tokens[token_count]=NULL;
      i--;
    }
  }
}

void execute_command(char *tokens[],int token_count){
  // Handles command execution via forking and execvp
  pid_t pid = fork();
  if(pid < 0){
    perror("Fork failed");
    exit(EXIT_FAILURE);
  } else if(pid == 0){
    // Child process
    handle_redirection(tokens,token_count);
    execvp(tokens[0], tokens); // Execute the command with the tokens as arguments
    perror("Execution failed"); // If execvp returns, it means it failed
    exit(EXIT_FAILURE);
  } else {
    // Parent process
    wait(NULL); // Wait for the child process to finish
  }
}

int split_commands(char *tokens[],int token_count,char *cmds[][100]){
  int cmd_index=0;
  int arg_index=0;
  for(int i=0;i<token_count;i++){
    if(strcmp(tokens[i],"|")==0){
      cmds[cmd_index++][arg_index]=NULL;
      if(cmd_index>10){
        fprintf(stderr, "Too many commands\n");
        exit(1);
      }
      arg_index=0;
    }else{
      cmds[cmd_index][arg_index++]=tokens[i];
    }
  }
  cmds[cmd_index][arg_index]=NULL;
  return cmd_index+1;
}

void execute_pipeline_commands(char *cmds[][100],int cmd_count){
  int pipes[cmd_count-1][2];
  for(int i=0;i<cmd_count-1;i++){
    if(pipe(pipes[i])<0){
      perror("Pipe failed");
      exit(1);
    }
  
  }
  for(int i=0;i<cmd_count;i++){
    pid_t pid=fork();
    if(pid < 0){
      perror("Fork failed");
      exit(EXIT_FAILURE);
    }else if(pid == 0){
      if(i==0){
        dup2(pipes[i][1],STDOUT_FILENO);
      }
      else if(i>0 && i<cmd_count-1){
        dup2(pipes[i-1][0],STDIN_FILENO);
        dup2(pipes[i][1],STDOUT_FILENO);
      }else if(i==cmd_count-1){
        dup2(pipes[i-1][0],STDIN_FILENO);
      }
      for(int j = 0; j < cmd_count - 1; j++){
        close(pipes[j][0]);
        close(pipes[j][1]);
      }
      int cmd_arg_count = 0;
      while(cmds[i][cmd_arg_count] != NULL){
        cmd_arg_count++;
      }
      handle_redirection(cmds[i],cmd_arg_count);
      execvp(cmds[i][0],cmds[i]);
      perror("exec failed");
      exit(1);
    }

  }
  for(int i=0;i<cmd_count-1;i++){
    close(pipes[i][0]);
    close(pipes[i][1]);
  }
  for(int i=0;i<cmd_count;i++){
    wait(NULL);
  }
}