#include <stdio.h>

void heapify(int array[], int index, int length);

int sortArray(int values[], int length){
	int i;
	//building the heap
	for(i = 0; i < length-1; i++){
		heapify(values, i, length);
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
	int values[10];
	int index;
	for(index = 0 ; index < 10; index++){
		values[index] = index;
	}
	sortArray(values, 10);
	
	for(index = 0; index < 10; index++){
		printf("%i\n",values[index]);
	}
	/* int index; */
	/* int values[128]; */
	/* int len = 128; */
	/* int val = 128; */

	/* for(index = 0; index < len; index++){ */
	/* 	values[index] = val; */
	/* 	val--; */
	/* } */

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
