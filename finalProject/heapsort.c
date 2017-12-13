#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void heapify(int array[], int index, int length);

float sortArray(int values[], int length){
	int i;
	struct timeval start_time, stop_time, elapsed_time;
	gettimeofday(&start_time, NULL);
	//building the heap, starting from the bottom most level
	for(i = length/2 - 1; i >= 0; i--){
		heapify(values, i, length);
	}
	for(i = length-1; i >= 0; i--){
		int swap = values[0];
		values[0] = values[i];
		values[i] = swap;
		heapify(values, 0, i);
	}
	gettimeofday(&stop_time, NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	return elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0;
}

void heapify(int array[], int index, int length){
	int indexLargest = index;
	//check if left child exists
	if((2*index)+1 < length){
		//check if left>parent
		if(array[(2*index)+1] > array[indexLargest]){
			indexLargest = (2*index)+1;
		}
		
	}
	//check if right child exists
	if((2*index)+2 < length){
		if(array[(2*index)+2] > array[indexLargest]){
			indexLargest = (2*index)+2;
		}
	}
	if(indexLargest != index){
		int swap = array[index];
		array[index] = array[indexLargest];
		array[indexLargest] = swap;
		heapify(array, indexLargest, length);
	}
}

//main driver of the code
int main(int argc, char *argv[]){
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
	printf("heapsort single threaded on backwards array len %i, threads: %f s \n", len, worstRunTime);
	float bestRunTime = sortArray(bestCase, len);
	printf("heapsort single threaded on sorted array len %i:, threads: %f\n",len, bestRunTime);
	float randomRunTime = sortArray(random, len);
	printf("heapsort single threaded on random array len %i:, threads: %f\n", len, randomRunTime);
	free(random);
	free(worstCase);
	free(bestCase);
}

