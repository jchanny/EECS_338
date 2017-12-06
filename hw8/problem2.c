#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <semaphore.h>
#include <sys/time.h>
#include <time.h>

#define PARENT 0
#define CHILD 1
#define N 10000

/* Global variables are shared by the thread(s) */
sem_t sem; // Semaphore
double global_min = 0; // Global minimum
int numThreads;

double shubert(double step, double x2);
void *child(); /* child thread */

int main(int argc, char *argv[])
{
	numThreads = atoi(argv[1]);
	struct timeval start_time, stop_time, elapsed_time;
	gettimeofday(&start_time,NULL);
	// Prepare semaphore
	if(sem_init(&sem, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}
	
	pthread_t threads[numThreads]; 
	pthread_attr_t attr; 
	pthread_attr_init(&attr);

		double sV = -2.0;
	double start[numThreads];
	double interval = 4/numThreads;

	int i;
	for(i = 0; i < numThreads; i++){
		start[i] = sV;
		sV = sV + interval;
	}
	
	for(i = 0 ; i < numThreads ; i++){
		pthread_create(&threads[i], &attr, child, &start[i] );
	}

	int loop;
	for(loop = 0 ; loop < numThreads ; loop++){
		pthread_join(threads[loop], NULL);
	}
	fflush(stdout);
	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	printf("Num cores=%d, execution time=%f s,min = %.2f ",numThreads,  elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, global_min);
}

void *child(void *arg) {
	double step = 0.001, x1_start, x1_stop, x1, x2, y;
	double *startVal = arg;
	double interval = 4.0/(double)numThreads;
	double end = *startVal+interval;
	
	for (x1 = *startVal; x1 <= end; x1 += step) {
		for (x2 = *startVal; x2 <= end; x2 += step) {
			y = shubert(x1, x2);
			sem_wait(&sem);
			if (y < global_min)
				global_min = y;
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
