#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void)
{
	char line[50];
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
  int should_run = 1;
	
	int i, upper;

  pid_t pid;

  while (should_run){
    printf("jeremy_shell>");
    fflush(stdout);
    gets(line);
    args[0] = strtok(line, " ");
    i = 0;
    while(args[i] != NULL){
      args[++i] = strtok(NULL, " ");
    }

    if(strcmp(args[0], "exit") == 0){
      exit(0);
    }
    else{
      fflush(stdout);
      pid = fork();

      if(pid == 0){
        execvp(args[0], args);
      }
      if(pid > 0){
        wait(NULL);
      }
    }
     
  }
    
	return 0;
}
