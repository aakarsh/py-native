#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int (*heap_cmp_t)(void* e1, void* e2);

typedef struct heap { 
	int capacity;
	int size;
	void** data;
	heap_cmp_t cmp;
} heap_t;

static inline int parent(int k)    { return k/2;        }
static inline int left(int k)      { return 2*k;        }
static inline int right(int k)     { return 2*k + 1;    }
static inline bool root(int index) { return index == 0; }

heap_t* heap_init(int capacity, heap_cmp_t cmp) { 
	heap_t* heap = malloc(sizeof(struct heap));
	heap->capacity = capacity;
	heap->size = 0;
	heap->data = malloc(sizeof(void*) * capacity);
	heap->cmp = cmp;
	return heap;
}

void heap_delete(heap_t * heap) { 
	free(heap);
}

static inline 
void heap_exch(heap_t* heap, int k, int pk){
	void* tmp = heap->data[k];	
	heap->data[k] = heap->data[pk];
	heap->data[pk] = tmp;
}

static inline 
void heap_sift_up(heap_t* heap, int k) {
	fprintf(stderr,"index : %d parent : %d\n", k , parent(k));
	while( k > 0 && heap->cmp(heap->data[k], heap->data[parent(k)] ) > 0) {
		int pk = parent(k);
		heap_exch(heap, k, pk);
		k = pk;
	}
}

static inline 
void heap_sift_down(heap_t* heap, int k) {
	fprintf(stderr,"index : %d parent : %d\n", k , parent(k));
	while( k > 0 /*&& heap->cmp(heap->data[k], heap->data[parent(k)] ) > 0*/) {
		int pk = parent(k);
		heap_exch(heap, k, pk);
		k = pk;
	}
}

int heap_insert(heap_t* heap, void* elem) { 
	if(heap->size >= heap->capacity) {
		fprintf(stderr, "heap reached capacity");
		return -1;
	}
	int k = heap->size;
	heap->data[k] = elem;	
	heap_sift_up(heap, k);
	heap->size++;
	return 0;
}

int int_cmp(int a , int b) { return a - b; }

void sort_file(char* file_name) { 
	FILE* file = fopen(file_name,"r");
	char* line = NULL;
	size_t linecap = 0 ; 
	ssize_t linelen;
	int nlines = 0;

	heap_t* heap = heap_init(100000, (heap_cmp_t) strcmp);

	while((linelen = getline(&line, &linecap, file)) > 0) { 
		heap_insert(heap, line);
		printf("insert [%s]\n",line);
		nlines++;
	}			

	int i;	
	for(i = 0 ; i < nlines; i++){
		printf("%d: [%s]\n",i,(char*) heap->data[i]);
	}

	fclose(file);

}

int main(int argc, char* argv[]) { 
	printf("[\n");

	int s[] ={3,1,2,10,9,7, 6,5,4,8};
	int len = 10;

	heap_t * heap = heap_init(len, (heap_cmp_t) &int_cmp);

	int i = 0;
	for(i = 0 ; i < len; i++){ 
		heap_insert(heap, &s[0]);
	}
	for(i = 0 ; i < len; i++) { 
		printf("%d " , i);
	}		

	printf("\n" );
	heap_delete(heap);
	sort_file("/etc/passwd");
	printf("]\n");
	return 0;
}

