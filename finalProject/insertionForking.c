#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void sortArray(int values[], int length){
	struct timeval start_time, stop_time, elapsed_time;
	int outerIndex;
	int currVal;
	gettimeofday(&start_time,NULL);
	
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
	timersub(&stop_time, start_time, &elapsed_time);
	printf("Run time of insertion sort w/forking: %f", elapsed_time.tv_sec+elapsed_time.tv_usec/100000.0);
}

int main(int argc, char *argv[]){
	//creating the unsorted array
	int temp;
	int index;
	int values[128];
	int len = 128;
	int val = 128;
	
	for(index = 0 ; index < len; index++){
		values[index] = val;
		val--;
	}

   	sortArray(values, len);

	int i;
	for(i = 0 ; i < len; i++){
		if(values[i] != i+1){
			printf("Insertion sort failed to sort properly.");
			return 0;
		}
	}
	printf("Insertion sort success!");
}
