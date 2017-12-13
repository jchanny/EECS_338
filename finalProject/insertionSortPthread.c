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

	if(numThreads == 2){
		mergeSubarrays(values, 0, sortInterval, sortInterval);
	}
	if(numThreads == 4){
		mergeSubarrays(values, 0, sortInterval, sortInterval);
		mergeSubarrays(values, sortInterval*2, sortInterval*3, sortInterval);
		mergeSubarrays(values, 0, sortInterval*2, sortInterval*2);
	}
				   
	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	return elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0;
}

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

	int numThreads = atoi(argv[2]); //num threads 2nd arg
	values = worstCase;
	float worstRunTime = sortArray(len, numThreads);
	printf("Insertion sort pthread on backwards array len %i, %i threads: %f s \n", len, numThreads, worstRunTime);
	values = bestCase;
	float bestRunTime = sortArray(len, numThreads);
	printf("Insertion sort pthread on sorted array len %i:, %i threads: %f\n",len, numThreads,bestRunTime);
	values = random;
	float randomRunTime = sortArray(len, numThreads);
	printf("Insertion sort pthread on random array len %i:, %i threads: %f\n", len, numThreads, randomRunTime);
	free(random);
	free(worstCase);
	free(bestCase);
	
}
