#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*heap_cmp_t)(void* e1, void* e2);

typedef struct heap{ 
    int size;
    void* data[];
    heap_cmp_t cmp;
} heap_t;

heap_t* init_heap(int size,int elem_size, heap_cmp_t cmp) { 
    heap_t* heap = malloc(sizeof(struct heap));
    heap->size = size;
    heap->data = malloc(sizeof(elem_size) * size);
    return heap;
}

void free_heap(heap_t * heap) { 
    free(heap);
}

int insert(void* elem) { 
    return 0;
}

int max(heap_t * h) { 
    return 0;
}

int extract_max(heap_t* h) { 
    return 0;
}

int main(int argc, char* argv[]) { 
    printf("begin\n");
    heap_t * heap = init_heap(10, (heap_cmp_t) strcmp);
    
    free_heap(heap);
    printf("end\n");
    return 0;
}
