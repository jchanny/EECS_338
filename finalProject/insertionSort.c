#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

float sortArray(int values[], int length){
	struct timeval start_time, stop_time, elapsed_time;
	int outerIndex;
	int currVal;
	gettimeofday(&start_time,NULL);
	for(outerIndex = 1 ; outerIndex < length; outerIndex++){
		currVal = values[outerIndex];
		int compareIndex = outerIndex -1;
		while(currVal < values[compareIndex] && compareIndex >= 0){
			int temp = values[compareIndex];
			values[compareIndex] = currVal;
			values[compareIndex+1] = temp;
			compareIndex--;
		}
	}
	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	return elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0;
}

int main(int argc, char *argv[]){
	//creating the unsorted array
	int temp;
	int index;
	int len = atoi(argv[1]); //length of array

	int *worstCase, *bestCase, *random;
	worstCase = (int*)calloc(len, sizeof(int));
	bestCase = (int*)calloc(len, sizeof(int));
	random = (int*)calloc(len, sizeof(int));

	int val = len;
	for(index = 0 ; index < len; index++){
		worstCase[index] = val;
		val--;
	}

	val = 1;
	for(index = 0; index < len ; index++){
		bestCase[index] = val;
		val++;
	}

	srand(time(NULL));
	for(index = 0; index < len; index++){
		int r = rand();
		random[index] = r;
	}

	float worstRunTime = sortArray(worstCase, len);
	printf("Insertion sort on backwards array len %i, %f s \n", len, worstRunTime);
	float bestRunTime = sortArray(bestCase, len);
	printf("Insertion sort on sorted array len %i:%f\n",len,bestRunTime);
	float randomRunTime = sortArray(random, len);
	printf("Insertion sort on random array len %i: %f\n", len, randomRunTime);
	free(random);
	free(worstCase);
	free(bestCase);
  
}
