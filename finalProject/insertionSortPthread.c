#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int *values;
//param: pass in array storing start and end pt of sort for thread
//startEndData[0] = start index of sort
//startEndData[1] = end index of sort
void *child(int *startEndData){
	int start = startEndData[0];
	int end = startEndData[1];
	int outerIndex;
	int currVal;
		for(outerIndex = start ; outerIndex < end; outerIndex++){
		currVal = values[outerIndex];
		int compareIndex = outerIndex -1;
		while(compareIndex >=0 && currVal < values[compareIndex] ){
			int temp = values[compareIndex];
			values[compareIndex] = currVal;
			values[compareIndex+1] = temp;
			compareIndex--;
		}
	}
}

//mergesort like merge
void mergeSubarrays(int arr[], int startOne, int startTwo, int lengthThread){
	int i;
	int indexOne, indexTwo;
	indexOne = startOne;
	indexTwo = startTwo;
	int work[lengthThread*2];
	for(i = 0; i < 2*lengthThread; i++){
		if(indexTwo >= startTwo+lengthThread){
			work[i] = arr[indexOne];
			indexOne++;
		}
		else if(indexOne >= startOne+lengthThread){
			work[i] = arr[indexTwo];
			indexTwo++;
		}
		else{
			if(arr[indexOne] < arr[indexTwo]){
				work[i] = arr[indexOne];
				indexOne++;
			}
			else{
				work[i] = arr[indexTwo];
				indexTwo++;
			}
		}
	}
	//recopy work into arr
	for(i = 0 ; i < 2*lengthThread; i++){
		arr[i] = work[i];
	}
}


float sortArray(int length, int numThreads){
	struct timeval start_time, stop_time, elapsed_time;
	pthread_t tid[numThreads];
	int outerIndex;
	int currVal;
	gettimeofday(&start_time,NULL);
	//creating new threads
	int sortInterval = length/numThreads;
	int i;
	for(i = 0 ; i < numThreads; i++){
		int intervalData[2];
		intervalData[0] = i*sortInterval;
		intervalData[1] = intervalData[0]+sortInterval;
		pthread_create(&tid[i], NULL, child, &intervalData);
	}

	for(i = 0; i < numThreads; i++){
		pthread_join(tid[i], NULL);
	}
				   
	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	return elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0;
}

int main(int argc, char *argv[]){
	int len = 10;
	int index;
	values = (int*)calloc(len, sizeof(int));
	values[0] = 2;
	values[1] = 5;
	values[2] = 1;
	values[3] = 3;
	values[4] = 0;
	values[5] = 11;
	values[6] = 8;
	values[7] = 9;
	values[8] = 7;
	values[9] = 6;

	sortArray(len, 2);

	for(index = 0 ; index < len; index++){
		printf("%i\n", values[index]);
	}
	//creating the unsorted array
/* 	int temp; */
/* 	int index; */
/* 	int len = 1000; */

/* 	int *worstCase, *bestCase, *random; */
/* 	worstCase = (int*)calloc(len, sizeof(int)); */
/* 	bestCase = (int*)calloc(len, sizeof(int)); */
/* 	random = (int*)calloc(len, sizeof(int)); */

/* 	int val = 1000; */
/* 	for(index = 0 ; index < len; index++){ */
/* 		worstCase[index] = val; */
/* 		val--; */
/* 	} */

/* 	val = 1; */
/* 	for(index = 0; index < len ; index++){ */
/* 		bestCase[index] = val; */
/* 		val++; */
/* 	} */

/* 	srand(time(NULL)); */
/* 	for(index = 0; index < len; index++){ */
/* 		int r = rand(); */
/* 		random[index] = r; */
/* 	} */

/* 	float worstRunTime = sortArray(worstCase, len); */
/* 	float bestRunTime = sortArray(bestCase, len); */
/* 	float randomRunTime = sortArray(random, len); */

/* 	int i; */
/* 	for(i = 1 ; i < len; i++){ */
/* 		if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){ */
/* 			printf("Insertion sort failed to sort properly."); */
/* 			return 0; */
/* 		} */
/* 	} */
/* 	printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime); */
/* 	printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime); */
/* 	printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime); */

/* free(random); */
/* 	free(worstCase); */
/* 	free(bestCase); */
/* 	//running insertion sort on len 2000 arrays */
/* 	len = 2000; */

/* 	worstCase = (int*)calloc(len, sizeof(int)); */
/* 	bestCase = (int*)calloc(len, sizeof(int)); */
/* 	random = (int*)calloc(len, sizeof(int)); */

/* 	val = 2000; */
/* 	for(index = 0 ; index < len; index++){ */
/* 		worstCase[index] = val; */
/* 		val--; */
/* 	} */

/* 	val = 1; */
/* 	for(index = 0; index < len ; index++){ */
/* 		bestCase[index] = val; */
/* 		val++; */
/* 	} */

/* 	srand(time(NULL)); */
/* 	for(index = 0; index < len; index++){ */
/* 		int r = rand(); */
/* 		random[index] = r; */
/* 	} */

/* 	worstRunTime = sortArray(worstCase, len); */
/* 	bestRunTime = sortArray(bestCase, len); */
/* 	randomRunTime = sortArray(random, len); */

	
/* 	for(i = 1 ; i < len; i++){ */
/* 		if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){ */
/* 			printf("Insertion sort failed to sort properly."); */
/* 			return 0; */
/* 		} */
/* 	} */
/* 	printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime); */
/* 	printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime); */
/* 	printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime); */

/* free(random); */
/* 	free(worstCase); */
/* 	free(bestCase); */
/* 		//running insertion sort on len 3000 arrays */
/* 	len = 3000; */

/* 	worstCase = (int*)calloc(len, sizeof(int)); */
/* 	bestCase = (int*)calloc(len, sizeof(int)); */
/* 	random = (int*)calloc(len, sizeof(int)); */

/* 	val = 3000; */
/* 	for(index = 0 ; index < len; index++){ */
/* 		worstCase[index] = val; */
/* 		val--; */
/* 	} */

/* 	val = 1; */
/* 	for(index = 0; index < len ; index++){ */
/* 		bestCase[index] = val; */
/* 		val++; */
/* 	} */

/* 	srand(time(NULL)); */
/* 	for(index = 0; index < len; index++){ */
/* 		int r = rand(); */
/* 		random[index] = r; */
/* 	} */

/* 	worstRunTime = sortArray(worstCase, len); */
/* 	bestRunTime = sortArray(bestCase, len); */
/* 	randomRunTime = sortArray(random, len); */

	
/* 	for(i = 1 ; i < len; i++){ */
/* 		if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){ */
/* 			printf("Insertion sort failed to sort properly."); */
/* 			return 0; */
/* 		} */
/* 	} */
/* 	printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime); */
/* 	printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime); */
/* 	printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime); */
	
}
