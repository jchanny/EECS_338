//Jeremy Chan jsc126
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define N 1000000000
#define MAX_LINE 80

int dumbsum(int sumTo){
  int x;

  for(int i = 0; i < sumTo ; i++){
    x = x+1;
  }
}

int main(void) {

  int numProcesses;
	pid_t pid, pidb, pidc;
	struct timeval start_time, stop_time, elapsed_time;  // timers
  char line[50];
  char *args[MAX_LINE/2 +1];

  printf("How many processes?");
  fflush(stdout);
  gets(line);
  numProcesses = atoi(line);

  if(numProcesses == 1){
    gettimeofday(&start_time, NULL);
    dumbsum(N);
    gettimeofday(&stop_time,NULL);
    timersub(&stop_time, &start_time, &elapsed_time);
    printf("Process 1 total time was %f seconds. Sum = %d.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N);
  }

  else if(numProcesses == 2){
    fflush(stdout);
    pid = fork();
    if(pid == 0){
      gettimeofday(&start_time, NULL);
      dumbsum(N/2);
      gettimeofday(&stop_time,NULL);
      timersub(&stop_time, &start_time, &elapsed_time);
      printf("Process 1 total time was %f seconds. Sum = %d.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/2);
    }
    else if(pid > 0){
      gettimeofday(&start_time, NULL);
      dumbsum(N/2);
      gettimeofday(&stop_time,NULL);
      timersub(&stop_time, &start_time, &elapsed_time);
      wait(NULL);
      printf("Process 2 total time was %f seconds. Sum = %d.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/2);
    }
  }

  else if(numProcesses == 3){
    fflush(stdout);
    pid = fork();

    if(pid == 0){
      gettimeofday(&start_time, NULL);
      dumbsum(N/3);
      gettimeofday(&stop_time, NULL);
      timersub(&stop_time, &start_time, &elapsed_time);
      printf("Process 2 total time was %f seconds. Sum = %d. \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/3);

    }
    else if(pid > 0){
      fflush(stdout);
      pidb = fork();

      gettimeofday(&start_time, NULL);
      dumbsum(N/3);
      gettimeofday(&stop_time, NULL);
      timersub(&stop_time, &start_time, &elapsed_time);
      printf("Process total time was %f seconds. Sum = %d. \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/3);
    }
  }
  else if(numProcesses == 4){
    fflush(stdout);
    pid = fork();

    if(pid == 0){
      pidb = fork();

      if(pidb == 0){
        gettimeofday(&start_time, NULL);
        dumbsum(N/4);
        gettimeofday(&stop_time, NULL);
        timersub(&stop_time, &start_time, &elapsed_time);
        printf("Process 1 total time was %f seconds. Sum = %d. \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/4);
      }
      else if(pidb > 0){
        gettimeofday(&start_time, NULL);
        dumbsum(N/4);
        gettimeofday(&stop_time, NULL);
        timersub(&stop_time, &start_time, &elapsed_time);
        printf("Process 2 total time was %f seconds. Sum = %d. \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/4);

      }
    }
    else if(pid > 0){
      pidc = fork();

      if(pidc == 0){
        gettimeofday(&start_time, NULL);
        dumbsum(N/4);
        gettimeofday(&stop_time, NULL);
        timersub(&stop_time, &start_time, &elapsed_time);
        printf("Process 3 total time was %f seconds. Sum = %d. \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/4);

      }
      else if(pidc > 0){
        gettimeofday(&start_time, NULL);
        dumbsum(N/4);
        gettimeofday(&stop_time, NULL);
        timersub(&stop_time, &start_time, &elapsed_time);
        printf("Process 4 total time was %f seconds. Sum = %d. \n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, N/4);

      }
    }
  }

	/* gettimeofday(&start_time,NULL); // Unix timer */
	/* pid = fork(); */
	/* if (pid > 0) { */
	/* 	for (i = 0; i < N; i++) { */
	/* 		x = x + 1; */
	/* 	} */
	/* 	gettimeofday(&stop_time,NULL); */
	/* 	timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine */
	/* 	printf("Parent total time was %f seconds. x = %lld.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, x); */
	/* } */
	/* else if (pid == 0) { /\* child process *\/ */
	/* 	for (i = 0; i < N; i++) { */
	/* 		x = x + 1; */
	/* 	} */
	/* 	gettimeofday(&stop_time,NULL); */
	/* 	timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine */
	/* 	printf("Child total time was %f seconds. x = %lld.\n", elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, x); */
	/* } */
}
