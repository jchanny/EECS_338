# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h>
#include <semaphore.h>

double shubert(double x1, double x2);

int main (int argc, char *argv[]){
	const int SIZE = 4069;
	const char *name = "minimum";
	int shm_fd;
	void *ptr;
	sem_t *sem;
	
	pid_t pid;
	double x1, x2, y;

	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	sem = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

	if(sem_init(sem, 1, 1) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		exit(0);
	}
	pid = fork();

	if(pid == 0){
		int min;

		for(x1 = -2 ; x1 <= 0 ; x1 += 0.5){
			for(x2 = -2; x2 <= 0 ; x2 += 0.5){
				y = shubert(x1,x2);
				printf("%.2f ", y);

				sem_wait(sem);
				if(y < min)
					min = y;
				sem_post(sem);
			}
			printf("\n", y);
		}
		char localMin[20];
		snprintf(localMin, 12, "%d", min);
		sprintf(ptr,"%s",localMin);
		ptr += strlen(localMin);
	}
	//parent
	else{
		int min, min2;
		for(x1 = 0 ; x1 <= 2 ; x1 += 0.5){
			for(x2 = 0; x2 <= 2 ; x2 += 0.5){
				y = shubert(x1,x2);
				printf("%.2f ", y);

				sem_wait(sem);
				if(y < min)
					min = y;
				sem_post(sem);
			}
			printf("\n", y);
		}

		wait(NULL);
		shm_fd = shm_open(name, O_RDONLY, 0666);
		ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
		min2 = atoi(ptr);
		if(min2 < min){
			printf("min= %d",min2);
		}
		else{
			printf("min=%d",min);
		}
		sem_destroy(sem);
		shm_unlink(name);
	}
	
	return 0;
}

double shubert(double x1, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((i + 1) * x1 + i);
		sum2 += i * cos((i + 1) * x2 + i);
	}
	return sum1 * sum2;
}
