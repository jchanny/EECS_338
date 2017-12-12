#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/mman.h>

void mergeSubarrays(int arr[], int startOne, int startTwo, int lengthThread);

void sortWrapper(int values[], int length, int numThreads){
	//initialize sempahores here
	int lengthThread = length/numThreads;
	int iProc;//index of the current process
	int proc;
	pid_t pid;
	int outerIndex;
	int currVal;

	int index2;

	int procCount = 0;
	

	int startSort = iProc*lengthThread;
	printf("startSort:%i, pid%i\n", startSort,getpid());
	int endSort = startSort + lengthThread;
	printf("endSort:%i\n", endSort);
	
	for(outerIndex = startSort ; outerIndex < endSort; outerIndex++){
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

float sortArray(int values[], int length, int numThreads){
	struct timeval start_time, stop_time, elapsed_time;

	int lengthThread = length/numThreads;
	gettimeofday(&start_time,NULL);
	sortWrapper(values, length, numThreads);
		
	int i;
	int startOne, startTwo;
	if(numThreads == 2){
		startOne = 0;
		startTwo = lengthThread;
		//	mergeSubarrays(values, startOne, startTwo, lengthThread);
	}
	if(numThreads == 4){
		
	}
	if(numThreads == 8){
	}

	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	return elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0;
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

int main(int argc, char *argv[]){
	int len = 2;
	char *name = "test";
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, len);
	int *values = mmap(0, len, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  
	int index;
	int val = 9;
	int arr[2];
	for(index = 0; index < len; index++){
		values[index] = val;
		val--;
	}

	sortArray(values, 2, 2);
	int index2;
	for(index2 = 0 ; index2 < 2; index2++){
		printf("%i\n", values[index2]);
	}
	//creating the unsorted array
	/* int temp;
	   /* int index;
	   /* int len = 1000; */

	/* int *worstCase, *bestCase, *random; */
	/* worstCase = (int*)calloc(len, sizeof(int)); */
	/* bestCase = (int*)calloc(len, sizeof(int)); */
	/* random = (int*)calloc(len, sizeof(int)); */

	/* int val = 1000; */
	/* for(index = 0 ; index < len; index++){ */
	/* 	worstCase[index] = val; */
	/* 	val--; */
	/* } */

	/* val = 1; */
	/* for(index = 0; index < len ; index++){ */
	/* 	bestCase[index] = val; */
	/* 	val++; */
	/* } */

	/* srand(time(NULL)); */
	/* for(index = 0; index < len; index++){ */
	/* 	int r = rand(); */
	/* 	random[index] = r; */
	/* } */

	/* float worstRunTime = sortArray(worstCase, len); */
	/* float bestRunTime = sortArray(bestCase, len); */
	/* float randomRunTime = sortArray(random, len); */

	/* int i; */
	/* for(i = 1 ; i < len; i++){ */
	/* 	if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){ */
	/* 		printf("Insertion sort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime); */
	/* printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime); */
	/* printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime); */

	/* free(random); */
	/* free(worstCase); */
	/* free(bestCase); */
	/* //running insertion sort on len 2000 arrays */
	/* len = 2000; */

	/* worstCase = (int*)calloc(len, sizeof(int)); */
	/* bestCase = (int*)calloc(len, sizeof(int)); */
	/* random = (int*)calloc(len, sizeof(int)); */

	/* val = 2000; */
	/* for(index = 0 ; index < len; index++){ */
	/* 	worstCase[index] = val; */
	/* 	val--; */
	/* } */

	/* val = 1; */
	/* for(index = 0; index < len ; index++){ */
	/* 	bestCase[index] = val; */
	/* 	val++; */
	/* } */

	/* srand(time(NULL)); */
	/* for(index = 0; index < len; index++){ */
	/* 	int r = rand(); */
	/* 	random[index] = r; */
	/* } */

	/* worstRunTime = sortArray(worstCase, len); */
	/* bestRunTime = sortArray(bestCase, len); */
	/* randomRunTime = sortArray(random, len); */

	/* i; */
	/* for(i = 1 ; i < len; i++){ */
	/* 	if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){ */
	/* 		printf("Insertion sort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime); */
	/* printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime); */
	/* printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime); */

	/* <<<<<<< HEAD */
	/* 			//running insertion sort on len 3000 arrays */
	/* 			======= */
	/* 			free(random); */
	/* free(worstCase); */
	/* free(bestCase); */
	/* //running insertion sort on len 3000 arrays */
	/* >>>>>>> betaVersion */
	/* 			len = 3000; */

	/* worstCase = (int*)calloc(len, sizeof(int)); */
	/* bestCase = (int*)calloc(len, sizeof(int)); */
	/* random = (int*)calloc(len, sizeof(int)); */

	/* val = 3000; */
	/* for(index = 0 ; index < len; index++){ */
	/* 	worstCase[index] = val; */
	/* 	val--; */
	/* } */

	/* val = 1; */
	/* for(index = 0; index < len ; index++){ */
	/* 	bestCase[index] = val; */
	/* 	val++; */
	/* } */

	/* srand(time(NULL)); */
	/* for(index = 0; index < len; index++){ */
	/* 	int r = rand(); */
	/* 	random[index] = r; */
	/* } */

	/* worstRunTime = sortArray(worstCase, len); */
	/* bestRunTime = sortArray(bestCase, len); */
	/* randomRunTime = sortArray(random, len); */

	/* i; */
	/* for(i = 1 ; i < len; i++){ */
	/* 	if(worstCase[i] < worstCase[i-1] || bestCase[i] < bestCase[i-1] || random[i] < random[i-1]){ */
	/* 		printf("Insertion sort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("Insertion sort on backwards array len %i:, %f \n", len, worstRunTime); */
	/* printf("Insertion sort on sorted array len %i:, %f\n",len,  bestRunTime); */
	/* printf("Insertion sort on random array len %i:, %f\n", len, randomRunTime); */
	
}
