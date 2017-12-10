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
int main(void){

	int index;
	int len = 1000;

	int *worstCase, *bestCase, *random;
	worstCase = (int*)calloc(len, sizeof(int));
	bestCase = (int*)calloc(len, sizeof(int));
	random = (int*)calloc(len, sizeof(int));

	int val = 1000;
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
	float bestRunTime = sortArray(bestCase, len);
	float randomRunTime = sortArray(random, len);

	int i;
	for(i = 1 ; i < len; i++){
		if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){
			printf("heapsort failed to sort properly.");
			return 0;
		}
	}
	printf("heapsort on backwards array len %i:, %f \n", len, worstRunTime);
	printf("heapsort on sorted array len %i:, %f\n",len,  bestRunTime);
	printf("heapsort on random array len %i:, %f\n", len, randomRunTime);

	//running insertion sort on len 2000 arrays
	len = 2000;

	worstCase = (int*)calloc(len, sizeof(int));
	bestCase = (int*)calloc(len, sizeof(int));
	random = (int*)calloc(len, sizeof(int));

	val = 2000;
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

	worstRunTime = sortArray(worstCase, len);
	bestRunTime = sortArray(bestCase, len);
	randomRunTime = sortArray(random, len);

	i;
	for(i = 1 ; i < len; i++){
		if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){
			printf("heapsort failed to sort properly.");
			return 0;
		}
	}
	printf("heapsort on backwards array len %i:, %f \n", len, worstRunTime);
	printf("heapsort on sorted array len %i:, %f\n",len,  bestRunTime);
	printf("heapsort on random array len %i:, %f\n", len, randomRunTime);

	//running insertion sort on len 3000 arrays
	len = 3000;

	worstCase = (int*)calloc(len, sizeof(int));
	bestCase = (int*)calloc(len, sizeof(int));
	random = (int*)calloc(len, sizeof(int));

	val = 3000;
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

	worstRunTime = sortArray(worstCase, len);
	bestRunTime = sortArray(bestCase, len);
	randomRunTime = sortArray(random, len);

	i;
	for(i = 1 ; i < len; i++){
		if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){
			printf("heapsort failed to sort properly.");
			return 0;
		}
	}
	printf("heapsort on backwards array len %i:, %f \n", len, worstRunTime);
	printf("heapsort on sorted array len %i:, %f\n",len,  bestRunTime);
	printf("heapsort on random array len %i:, %f\n", len, randomRunTime);
	return 0;
}

