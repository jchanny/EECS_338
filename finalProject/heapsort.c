#include <stdio.h>

void heapify(int array[]);
void buildHeap(int array[]);

int sortArray(int values[], int length){
	
}

//creates heap in place,
/*ith element:
left child @ 2i
right child @2i+1
parent @ i/2*/
void buildHeap(int array[]){
	
}

void heapify(int array[]){
}

int main(void){
	int index;
	int values[128];
	int len = 128;
	int val = 128;

	for(index = 0; index < len; index++){
		values[index] = val;
		val--;
	}

	/* sortArray(values, len); */

	/* int i; */
	/* for(i = 0 ; i < len; i++){ */
	/* 	if(values[i] != i+1){ */
	/* 		printf("Heap sort failed to sort properly."); */
	/* 		return 0; */
	/* 	} */
	/* } */
	/* printf("Heap sort success!"); */

}
