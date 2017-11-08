# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>

double shubert(double x1, double x2);
double min, min2;

int *runShubert(){
	double i,j,y2;
	for(i = 0 ; i <= 2; i += 0.5){
		for(j = 0; j <=2 ; j += 0.5){
			y2 = shubert(i,j);
			printf("%.2f ",y2);
			if(y2 < min2)
				min2 = y2;
		}
		printf("\n", y2);
	}
	return 0;
}

int main (int argc, char *argv[]){
 	pthread_t tid;
	double x1, x2, y;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_create(&tid,&attr,runShubert,NULL);

	for(x1 = -2 ; x1 <= 0 ; x1 += 0.5){
		for(x2 = -2; x2 <= 0 ; x2 += 0.5){
			y = shubert(x1,x2);
			printf("%.2f ", y);
			if(y < min)
				min = y;
		}
		printf("\n", y);
	}

	pthread_join(tid,NULL);

	if(min < min2)
		printf("min = %.2f \n", min);
	else
		printf("min = %.2f \n", min2);
	
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
