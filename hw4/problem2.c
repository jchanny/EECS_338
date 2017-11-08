# include <stdlib.h>
# include <stdio.h>
# include <math.h>

double shubert(double x1, double x2);

int pipeTest(){
	double x1, x2, y, min = 0;
	int fd[2];
	pid_t pid;
	float min2;
	pipe(fd);

	pid = fork();

	if(pid == 0){
		for(x1 = -2; x1 <= 0; x1 += 0.5){
			for(x2 = -2; x2 <= 0 ; x2 += 0.5){
				y = shubert(x1, x2);
				printf("%.2f ", y);
				if(y < min2)
					min2 = y;
			}
			printf("\n", y);
		}
		//pipe the min into the parent process
		close(fd[0]);
		write(fd[1], &min2, sizeof(min2));
		close(fd[1]);
		exit(0);
	}
	else{
		for(x1 = 0; x1 <= 2; x1 += 0.5){
			for(x2 = 0; x2 <= 2; x2 += 0.5){
				y = shubert(x1, x2);
				printf("%.2f ", y);
				if(y < min)
					min = y;
			}
			printf("\n", y);
		}

		//need to close before receiving data
		close(fd[1]);
		wait(NULL);
		read(fd[0], &min2, sizeof(min2));
		if(min2 < min)
			min = min2;
		printf("min = %.2f \n",min);
	}
	return 0;
}

int main (){
	pipeTest();
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
