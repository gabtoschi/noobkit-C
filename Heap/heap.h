#ifndef _HEAP_H_
#define _HEAP_H_

typedef struct {
	int vertex;
	int cost;
} HeapData;

typedef struct {
	HeapData *data;
	int d;
	int size;
} Heap;

Heap *heapCreate();
void heapDestroy(Heap *);
void heapInsert(Heap *, HeapData);
void heapPrint(Heap *);
HeapData heapRemove(Heap *);
int heapGetCost(Heap *, int);
void heapUpdate(Heap *, int, int);
int heapEmpty(Heap *);

#endif