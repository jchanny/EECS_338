#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(){
  const int SIZE = 4096;
  const char *name = "OS";
  const char *message = "ayy yo waddup \n";

  int shm_fd, pid;
  void *ptr;

  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);

  ptr = mmap(0,SIZE,PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  pid = fork();

  if(pid == 0){
    sprintf(ptr, "%s", message);
    ptr += strlen(message);
  }
  if(pid > 0){
    wait(NULL);
    shm_fd = shm_open(name, O_RDONLY, 0666);
    ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    printf("%s", ptr);
    shm_unlink(name);
    //now we read/print message and unlink memory
  }
  return 0;
}
