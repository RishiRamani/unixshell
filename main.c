#include <stdio.h>
#include <stdlib.h>

int main(void){
  char input[1024];
  while(1){
    printf("myshell> ");
    fflush(stdout);
    if(fgets(input, sizeof(input), stdin) == NULL){
      break;
    }
    printf("You typed: %s", input);
  }
  return 0;
}