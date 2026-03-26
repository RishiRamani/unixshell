#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void){
  char input[1024];
  char * tokens[100]; // Array to hold pointers to tokens 
  int token_count;

  while(1){
    printf("myshell> ");
    fflush(stdout);
    if(fgets(input, sizeof(input), stdin) == NULL){ // fgets returns NULL if it encounters EOF or an error
      printf("\nExiting shell.\n");
      break;
    }


    token_count=0; // Reset token count for each new input
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

    pid_t pid = fork();
    if(pid < 0){
      perror("Fork failed");
      exit(EXIT_FAILURE);
    } else if(pid == 0){
      // Child process
      execvp(tokens[0], tokens); // Execute the command with the tokens as arguments
      perror("Execution failed"); // If execvp returns, it means it failed
      exit(EXIT_FAILURE);
    } else {
      // Parent process
      wait(NULL); // Wait for the child process to finish
    }
    
    for(int i=0; i<token_count; i++){
      printf("Token %d: %s\n", i, tokens[i]);
    }
  }
  return 0;
}