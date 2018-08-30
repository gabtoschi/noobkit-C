#include <stdlib.h>
#include <stdio.h>

#include "heap.h"

#define Root 0

int parent(int i, int d){
	return (i-1) / d;
}

int child(int i, int d, int n){
	return (d*i) + n;
}

void heapSwap(Heap *h, int a, int b){
	HeapData aux = h->data[a];
	h->data[a] = h->data[b];
	h->data[b] = aux;
}

int heapCompareData(HeapData a, HeapData b){
	if (a.cost == b.cost) return a.vertex - b.vertex;
		else return a.cost - b.cost;
}

Heap *heapCreate(){
	Heap *h = (Heap *) calloc(1, sizeof(Heap));
	h->d = 2; // cada no da heap tera 2 filhos
	return h;
}

void heapDestroy(Heap *h){
	free(h->data);
	free(h);
}

void heapInsert(Heap *h, HeapData a){
	h->data = (HeapData *) realloc(h->data, sizeof(HeapData) * (h->size + 1));
	int i = h->size;
	h->data[h->size++] = a;

	// heap up
	//while (i >= 0 && h->data[i].cost < h->data[parent(i, h->d)].cost){
	while (i >= 0 && heapCompareData(h->data[i], h->data[parent(i, h->d)]) < 0){
		heapSwap(h, i, parent(i, h->d));
		i = parent(i, h->d);
	}
}

int heapGetMinChild(Heap *h, int i){
	int j;
	int min = i;

	for (j = 1; j <= h->d; j++){
		//if (child(i, h->d, j) < h->size && h->data[child(i, h->d, j)].cost < h->data[min].cost){
		if (child(i, h->d, j) < h->size && heapCompareData(h->data[child(i, h->d, j)], h->data[min]) < 0){
			min = child(i, h->d, j);
		}
	}

	return min;
}

void heapDown(Heap *h, int i){
	int min = heapGetMinChild(h, i);

	if (min != i){
		heapSwap(h, i, min);
		heapDown(h, min);
	}
}

void heapPrint(Heap *h){
	int i;
	for (i = 0; i < h->size; i++) printf("%d (%d)\n", h->data[i].vertex, h->data[i].cost);
	printf("\n");
}

HeapData heapRemove(Heap *h){
	HeapData key = h->data[Root];

	heapSwap(h, Root, h->size-1);
	h->size--;
	h->data = (HeapData *) realloc(h->data, sizeof(HeapData) * h->size);

	heapDown(h, Root);

	return key;
}

int heapGetCost(Heap *h, int v){
	int i;
	for (i = 0; i < h->size; i++)
		if (h->data[i].vertex == v) return h->data[i].cost;

	return -1;
}	

void heapUpdate(Heap *h, int v, int new){
	int i;
	for (i = 0; i < h->size; i++)
		if (h->data[i].vertex == v) break;
	
	h->data[i].cost = new;

	// heap up
	//while (i >= 0 && h->data[i].cost < h->data[parent(i, h->d)].cost){
	while (i >= 0 && heapCompareData(h->data[i], h->data[parent(i, h->d)]) < 0){
		heapSwap(h, i, parent(i, h->d));
		i = parent(i, h->d);
	}
}	

int heapEmpty(Heap *h){
	if (h->size == 0) return 1;
		else return 0;
}
