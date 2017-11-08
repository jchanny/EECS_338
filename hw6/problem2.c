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

sem_t wrt;
sem_t mutex;
int read_count = 0;
char buffer[50];
int version;

int *runner(){
	int prevVersion;
	prevVersion= 0;
	
	do{
	sem_wait(&mutex);
		read_count++;
		if(read_count == 1){
			sem_wait(&wrt);
		}
		sem_post(&wrt);
		sem_post(&mutex);

		if(prevVersion < version){
				long long tid = (long long) pthread_self();

			printf("ID: %d, message: %s \n", tid, buffer);
			prevVersion++;
		}

		sem_wait(&mutex);

		read_count--;

		if(read_count == 0){
			sem_post(&wrt);
		}
		sem_post(&mutex);
	
	}while(prevVersion != 2);
	
	pthread_exit(0);
	return 0;
}

int main(){
	pthread_t tid1, tid2;
	pthread_attr_t attr;
	version = 0;
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, runner, NULL);
	pthread_create(&tid2, &attr, runner, NULL);

	sem_init(&mutex, 1, 1);
	sem_init(&wrt, 1, 1);

	sem_wait(&wrt);
	strcpy(buffer, "Roses are red");
	version++;
	sem_post(&wrt);

	sleep(1);
	sem_wait(&wrt);
	strcpy(buffer, "I'm out of ideas");
	version++;
	sem_post(&wrt);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	sem_destroy(&wrt);
	sem_destroy(&mutex);
	
	return 0;
}

