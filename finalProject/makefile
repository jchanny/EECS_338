all: ha hb hc hd ia ib ic id

ha:
	-gcc -o heapsort heapsort.c
hb:
	-gcc -o heapsortForking heapsortForking.c -pthread -lrt
hc:
	-gcc -o heapsortOpenMp heapsortOpenMp.c -fopenmp
hd:
	-gcc -o heapsortPthread heapsortPthread.c -pthread -lrt

ia:
	-gcc -o insertionSort insertionSort.c
ib:
	-gcc -o insertionSortForking insertionForking.c -pthread -lrt
ic:
	-gcc -o insertionSortOpenMp insertionSortOpenMp.c -fopenmp
id:
	-gcc -o insertionSortPthread insertionSortPthread.c -pthread -lrt

