#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

float sortArray(int values[], int length, int numThreads){
	struct timeval start_time, stop_time, elapsed_time;

	int outerIndex;
	int currVal;
	gettimeofday(&start_time,NULL);
	int lengthThread = length/numThreads;
	int iProc;//index of the current process
	int proc;

	for(proc = 0; proc < numThreads; proc++){
		pid = fork();
		if(!pid){
			iProc = proc;
		}
	}
	int startSort = iProc*lengthThread;
	int endSort = startSort + lengthThread;
	
	for(outerIndex = startSort ; outerIndex < endSort; outerIndex++){
		currVal = values[outerIndex];
		int compareIndex = outerIndex -1;
		while(currVal < values[compareIndex] && compareIndex >= 0){
			int temp = values[compareIndex];
			values[compareIndex] = currVal;
			values[compareIndex+1] = temp;
			compareIndex--;
		}
	}
	wait(NULL);
	//after joining all of the subarrays, merge all the subarrays together
	int i;
	//figure out how to merge the arrays together

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

free(random);
	free(worstCase);
	free(bestCase);
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

<<<<<<< HEAD
	//running insertion sort on len 3000 arrays
=======
free(random);
	free(worstCase);
	free(bestCase);
		//running insertion sort on len 3000 arrays
>>>>>>> betaVersion
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
