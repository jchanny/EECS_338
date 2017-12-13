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

void mergeSubarrays(int arr[], int work[], int startOne, int startTwo, int lengthThread);

void sortWrapper(int *values, int start, int end){
	//initialize sempahores here
	int iProc;//index of the current process
	int proc;
	pid_t pid;
	int outerIndex;
	int currVal;

	int index;
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

int* setup_memory(char *name, int size){
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, size);
	int *m = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(m == MAP_FAILED){
		printf("map failed\n");
		exit(-1);
	}
	return m;
}

float sortArray(int values[], int length, int numThreads){
	struct timeval start_time, stop_time, elapsed_time;
	char *name2 = "unsorted";
	char *name = "sorted";

	const int SIZE = length * sizeof(int);
	int *unsortedArray = setup_memory(name2, SIZE);
	int *sortedArray = setup_memory(name, SIZE);
	
	int lengthThread = length/numThreads;
	gettimeofday(&start_time,NULL);

	//copy the contents of values into the unsorted helper array
	int i;
	for(i = 0 ; i < length; i++){
		unsortedArray[i] = values[i];
	}
	//create child processes
	pid_t pid;
	int iProc = 0;
	int nextProc;
	for(nextProc = 1; nextProc < numThreads & !pid; nextProc++){
		pid = fork();
		if(!pid)
			iProc = nextProc;
	}
	int start = iProc * lengthThread;
	int end = start+lengthThread;

	sortWrapper(unsortedArray, start, end);
	
	for(i = numThreads - 1; i > 0 ; i--){
		if(iProc == i)
			return 0;
		else
			wait(NULL);
	}

	if(numThreads == 2){
		mergeSubarrays(unsortedArray,sortedArray, 0, lengthThread, lengthThread);
	}
	if(numThreads == 4){
		mergeSubarrays(unsortedArray, sortedArray, 0, lengthThread, lengthThread);
		mergeSubarrays(unsortedArray, sortedArray, 2*lengthThread, 3*lengthThread, lengthThread);
		mergeSubarrays(unsortedArray, sortedArray, 0, 2*lengthThread, lengthThread*2);
	}

	int indexTemp;
	for(indexTemp = 0 ; indexTemp < length; indexTemp++){
		values[indexTemp] = sortedArray[indexTemp];
	}

	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time);
	return elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0;
}

//mergesort like merge
void mergeSubarrays(int arr[], int work[],int startOne, int startTwo, int lengthThread){
	int i;
	int indexOne, indexTwo;
	indexOne = startOne;
	indexTwo = startTwo;
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
	float worstRunTime = sortArray(worstCase, len, numThreads);
	printf("Insertion sort fork on backwards array len %i, %i threads: %f s \n", len, numThreads, worstRunTime);
	float bestRunTime = sortArray(bestCase, len, numThreads);
	printf("Insertion sort fOrk on sorted array len %i:, %i threads: %f\n",len, numThreads,bestRunTime);
	float randomRunTime = sortArray(random, len, numThreads);
	printf("Insertion sort fork on random array len %i:, %i threads: %f\n", len, numThreads, randomRunTime);
	free(random);
	free(worstCase);
	free(bestCase);
	
	
}
