#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void *child(int *values[], int *start, int *interval){
	int i;
	int currVal;
	for(outerIndex = start ; outerIndex < start+interval; outerIndex++){
		currVal = values[outerIndex];
		int compareIndex = outerIndex -1;
		while(currVal < values[compareIndex] && compareIndex >= 0){
			int temp = values[compareIndex];
			values[compareIndex] = currVal;
			values[compareIndex+1] = temp;
			compareIndex--;
		}
	}

}

float sortArray(int values[], int length, int numThreads){
	struct timeval start_time, stop_time, elapsed_time;
	pthread_t tid[numThreads];
	int outerIndex;
	int currVal;
	gettimeofday(&start_time,NULL);
	//creating new threads
	int sortStart[numThreads];
	int sortInterval = length/numThreads;
	int i;
	for(i = 0 ; i < numThreads; i++){
		sortStart[i] = 1 + i*sortInterval;
		pthread_create(&tid[i], NULL, child, &values, &sortStart[i], &sortInterval);
	}

	for(i = 0; i < numThreads; i++){
		pthread_join(tid[i], NULL);
	}
	//do one final sort over array once all the subarrays from child threads merged
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
			printf("Insertion sort failed to sort properly.");
			return 0;
		}
	}
	printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime);
	printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime);
	printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime);

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
			printf("Insertion sort failed to sort properly.");
			return 0;
		}
	}
	printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime);
	printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime);
	printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime);

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
			printf("Insertion sort failed to sort properly.");
			return 0;
		}
	}
	printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime);
	printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime);
	printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime);
	
}
