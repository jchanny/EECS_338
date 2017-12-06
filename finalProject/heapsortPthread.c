#include <stdio.h>
#include <pthread.h>

void heapify(int array[], int index, int length);

void *child(void *values[], void *start, void *sortLength){
	int i;
	for(i = *start-1; start >= *start-1-*sortLength; i--){
		int swap = values[0];
		values[0] = values[i];
		values[i] = swap;
		heapify(values, 0, i-1);
	}
}

int sortArray(int values[], int length, int numThreads){
	int i;
	pthread_t tid[numThreads];
	int threadStart[numThreads];
	
	//building the heap
	for(i = 0; i < length-1; i++){
		heapify(values, i, length);
	}
	int sortLen = length/numThreads;
	//multithreading will occur here:
	for(i = 0; i < numThreads; i++){
		threadStart[i] = i*sortLen;
		pthread_create(&tid[i],NULL, child, &values, &threadStart[i], &sortLen);
	}

	for(i = 0; i < numThreads; i++){
		pthread_join(tid[i], NULL);
	}
	//swap 0th element w/last, heapify
	for(i = length-1; i >= 0; i--){
		int swap = values[0];
		values[0] = values[i];
		values[i] = swap;
		heapify(values, 0, i-1);
	}
}

//creates heap in place,
/*ith element:
  left child @ 2i
  right child @2i+1
  parent @ i/2*/
void heapify(int array[], int index, int length){
	if(index < length-1){
	//left child
	if(index % 2 == 0){
		if(array[index+1] > array[(index+1)/2]){
			//swap parent and current
			int parent = array[(index+1)/2];
			array[(index+1)/2] = array[index+1];
			array[index+1] = parent;

			int newIndex = (index+1)/2;
			if(newIndex!= 0){
				heapify(array, newIndex-1, length);
			}
		}
	}
	//right child
	else{
		if(array[index+1] > array[((index+1)/2)-1]){
			int parent = array[((index+1)/2)-1];
			array[((index+1)/2)-1] = array[index+1];
			array[index+1] = parent;
			int newIndex = ((index+1)/2)-1;
			if(newIndex != 0){
				heapify(array, newIndex-1, length);
			}
		}
	}
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
	
}
