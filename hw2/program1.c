#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
  int pid, pidb;
  printf("I'm the parent. Process 1 = %d. parent = %d\n", getpid(), getppid());
  fflush(stdout);
  pid = fork();

  if(pid > 0){
    fflush(stdout);
    pidb = fork();
    sleep(2);
    //if current process is not child process (its currently parent), do nothing
    if(pidb > 0){
    }
    else{
      printf("I'm a child of parent, process 3 = %d, parent =%d\n", getpid(), getppid());
    }
  }
  //this if statement effectively creates a new process
  else if(pid == 0){
    printf("I'm a child of parent, process 2 = %d, parent = %d\n", getpid(), getppid());
  }
  
  return 0;
}

