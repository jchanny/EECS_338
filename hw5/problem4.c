# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <semaphore.h>
#include <errno.h>
#include <unistd.h>     
#include <sys/types.h>  

double shubert(double x1, double x2);
double min;
sem_t sem;

int *runShubert(){
	double i,j,y2;
	for(i = 0 ; i <= 2; i += 0.5){
		for(j = 0; j <=2 ; j += 0.5){
			y2 = shubert(i,j);
			printf("%.2f ",y2);

			sem_wait(&sem);
			if(y2 < min)
				min = y2;
			sem_post(&sem);
		}
		printf("\n", y2);
	}
	pthread_exit(0);
	return 0;
}

int main (int argc, char *argv[]){
 	pthread_t tid;
	double x1, x2, y;
	pthread_attr_t attr;

	if(sem_init(&sem,0,1) < 0){
		exit(0);
	}
	
	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,runShubert,NULL);

	for(x1 = -2 ; x1 <= 0 ; x1 += 0.5){
		for(x2 = -2; x2 <= 0 ; x2 += 0.5){
			y = shubert(x1,x2);
			printf("%.2f ", y);

			sem_wait(&sem);
			if(y < min)
				min = y;
			sem_post(&sem);
		}
		printf("\n", y);
	}

	pthread_join(tid,NULL);
	sem_destroy(&sem);
	printf("min = %.2f \n", min);

	
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
