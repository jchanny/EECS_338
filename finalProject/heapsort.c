#include <stdio.h>

void heapify(int array[], int index, int length);

int sortArray(int values[], int length){
	int i;
	//building the heap
	for(i = 0; i < length-1; i++){
		heapify(values, i, length);
	}
	//swap 0th element w/last, heapify
	/* for(i = length -1; i >=0 ; i--){ */
	/* 	int swap = values[0]; */
	/* 	values[0] = values[i]; */
	/* 	values[i] = swap; */
		
	/* } */
	/* for(i = length-1; i >= 0; i--){ */
	/* 	int swap = values[0]; */
	/* 	values[0] = values[i]; */
	/* 	values[i] = swap; */
	/* 	heapify(values, 0, i-1); */
	/* } */
}

/*input: root node, looks at both of its children*/
void heapify(int array[], int index, int length){length
	if(2*(index+1) >= length || 2*(index+1)-1 >= length){}
	else{
		//if left child bigger
		if(array[(2*(index+1))-1] > array[index]){
			int swap = array[index];
			array[index] = array[(2*(index+1))-1];
			array[(2*(index+1))-1] = swap;
			
			heapify(array, (2*(index+1))-1, length);
		}
		//if right child bigger
		if(array[2*(index+1)] > array[index]){
			int swap = array[index];
			array[index] = array[2*(index+1)];
			array[2*(index+1)] = swap;
			//	if(2*(index+1) < length)
				heapify(array, 2*(index+1), length);
		}
	}
}


//main driver of the code
int main(void){

	int index;
	int len = 10;
	int arr[10];
	int val = 0;
	for(index = 0; index< len; index++){
		arr[index] = val;
		val++;
	}

	int array[3];
	array[0] = 0;
	array[1] = 1;
	array[2] = 2;
	array[3] = 3;
	array[4] = 4;
	sortArray(array, 5);
	//	sortArray(arr, len);
	for(index = 0; index < 5; index++)
		printf("%i\n", array[index]);

	/* for(index = 0; index < len ; index++){ */
	/* 	printf("%i\n",arr[index]); */
	/* } */
  
	/* int index; */
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
	/* 		printf("heapsort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("heapsort on backwards array len %i:, %f \n", len, worstRunTime); */
	/* printf("heapsort on sorted array len %i:, %f\n",len,  bestRunTime); */
	/* printf("heapsort on random array len %i:, %f\n", len, randomRunTime); */

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
	/* 		printf("heapsort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("heapsort on backwards array len %i:, %f \n", len, worstRunTime); */
	/* printf("heapsort on sorted array len %i:, %f\n",len,  bestRunTime); */
	/* printf("heapsort on random array len %i:, %f\n", len, randomRunTime); */

	/* //running insertion sort on len 3000 arrays */
	/* len = 3000; */

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
	/* 		printf("heapsort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("heapsort on backwards array len %i:, %f \n", len, worstRunTime); */
	/* printf("heapsort on sorted array len %i:, %f\n",len,  bestRunTime); */
	/* printf("heapsort on random array len %i:, %f\n", len, randomRunTime); */
	
}
