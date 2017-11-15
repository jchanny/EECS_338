#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <semaphore.h>
#include <time.h>

#define PARENT 0
#define CHILD 1
#define N 10000

sem_t sem; 
double global_min = 0; 
int numThreads;

double shubert(double step, double x2);
void *child(void *arg); 

int main(int argc, char*argv[])
{
	numThreads = atoi(argv[1]);
	double executionTime;
	clock_t begin = clock();
	
	if(sem_init(&sem, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}
	// Prepare the child thread
	pthread_t threads[numThreads]; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	double sV = -2.0;
	double start[numThreads];
	double interval = 4/numThreads;

	for(int i = 0; i < numThreads; i++){
		start[i] = sV;
		sV = sV + interval;
	}
	
	for(int loop = 0 ; loop < numThreads; loop++){
		pthread_create(&threads[loop],&attr,child,&start[loop]);
	}

	for(int i = 0 ; i < numThreads; i++){
		pthread_join(threads[i], NULL);
	}
	clock_t end = clock();
	executionTime = (double)(end-begin)/CLOCKS_PER_SEC;
	printf("min = %.2f ", global_min);
}

void *child(void *arg) {
	double step = 0.005, x1_stop, x1, x2, y;
	double *startVal = arg;
	double interval = 4/numThreads;
	double end = *startVal+interval;
	printf("%d\n", numThreads);
	for (x1 = *startVal; x1 <= end; x1 += step) {
		for (x2 = *startVal; x2 <= end ; x2 += step) {
			y = shubert(x1, x2);
			// *** ENTRY FOR CRITICAL SECTION ***
			sem_wait(&sem);
			// *** BEGIN CRITICAL SECTION ***
			if (y < global_min)
				global_min = y;
			// *** EXIT FROM CRITICAL SECTION ***
			sem_post(&sem);
		}
	}
	pthread_exit(0);
}

double shubert(double step, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((i + 1) * step + i);
		sum2 += i * cos((i + 1) * x2 + i);
	}
	return sum1 * sum2;
}
