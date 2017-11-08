#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

double shubert(double x1, double x2);

int main (){

	int tid;
	double min;
	
	#pragma omp parallel
	{
		tid = omp_get_thread_num();
		//if master thread
		if(tid == 0){
			double x1, x2, y;
			
			for(x1 = -2; x1 <= 0; x1+=0.5){
				for(x2 = -2; x2 <= 0; x2 +=0.5){
					y = shubert(x1,x2);
					printf("%.2f ",y);
					#pragma omp critical
					{
						if(y < min)
							min = y;
					}
				}
				printf("\n", y);
			}

		}
		else{
			double x3, x4, y2;

			for(x3 = 0; x3 <= 2; x3+=0.5){
				for(x4 = 0; x4 <= 2; x4+=0.5){
					y2 = shubert(x3, x4);
					printf("%.2f ",y2);
					#pragma omp critical
					{
						if(y2 < min)
							min = y2;
					}
				}
				printf("\n", y2);
			}

		}
	}
	printf("min = %.2f ",min);
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
