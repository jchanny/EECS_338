#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>

double shubert(double x1, double x2);

int main (){
	struct timeval start_time, stop_time, elapsed_time;
	gettimeofday(&start_time,NULL);
	int tid;
	double min;
	int	numCores = omp_get_num_threads();
	
	#pragma omp parallel
	{
		tid = omp_get_thread_num();
		//if master thread
		if(tid == 0){
			double x1, x2, y;
			
			for(x1 = -2; x1 <= 0; x1+=0.001){
				for(x2 = -2; x2 <= 0; x2 +=0.001){
					y = shubert(x1,x2);
					#pragma omp critical
					{
						if(y < min)
							min = y;
					}
				}
			}

		}
		else{
			double x3, x4, y2;

			for(x3 = 0; x3 <= 2; x3+=0.001){
				for(x4 = 0; x4 <= 2; x4+=0.001){
					y2 = shubert(x3, x4);
					#pragma omp critical
					{
						if(y2 < min)
							min = y2;
					}
				}
			}

		}
	}
	gettimeofday(&stop_time, NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	printf("I am running %d cores and I took %f seconds to execute. Min = %.2f\n", numCores, elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0 ,min);
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
