#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>      
#include <pthread.h>    
#include <semaphore.h>

sem_t empty;
sem_t lock ;
sem_t full ;
int buffer[5];

int *runner(){
	for(int loop = 0; loop < 10; loop++){
			sem_wait(&full);
				sem_wait(&lock);
		printf("%i \n", buffer[loop%5]);
		sem_post(&lock);
		sem_post(&empty);
	}
	pthread_exit(0);
	return 0;
}

int main(){

	pthread_t tid;
	pthread_attr_t attr;

	sem_init(&full, 1,0);
	sem_init(&lock,1,1);
	sem_init(&empty,1,5);
	
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, runner, NULL);
	int currVal;

	for(int loop = 0 ; loop < 10; loop++){
		currVal = loop;
		sem_wait(&empty);
		sem_wait(&lock);
		buffer[loop%5] = currVal;
		sem_post(&lock);
		sem_post(&full);
	}

	pthread_join(tid, NULL);
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&lock);
	return 0;
}
