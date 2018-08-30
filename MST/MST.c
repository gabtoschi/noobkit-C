#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "mgraph.h"
#include "heap.h"

#define INF INT_MAX
#define isAdded 1

int *MST(MGraph *g, int start, int **MSTorder){
	int i;
	HeapData v;
	int *adj;
	int vertQuant = getVerticesQuantM(g);

	// inicializando fila de prioridades
	Heap *Q = heapCreate();
	HeapData aux;
	aux.cost = INF;
	for (i = 0; i < vertQuant; i++){
		aux.vertex = i;
		heapInsert(Q, aux);
	}

	// inicializando vetor de predecessores
	int *pred = (int *) malloc(sizeof(int) * vertQuant);
	for (i = 0; i < vertQuant; i++) pred[i] = NoEdge;

	// inicializando vetor de ordem de entrada
	int *order = (int *) malloc(sizeof(int) * vertQuant);
	int orderTop = -1;

	// inicializando vetor de checagem de entrada
	int *addCheck = (int *) calloc(vertQuant, sizeof(int));

	// atualizando custo do vetor inicial
	heapUpdate(Q, start, 0);

	// enquanto a fila de prioridades tiver vertices
	while (!heapEmpty(Q)){
		// extraia o vertice com menor peso
		v = heapRemove(Q);

		// insira ele na MST
		order[++orderTop] = v.vertex;
		addCheck[v.vertex] = isAdded;

		// pegue os adjacentes do vertice
		adj = getAdjacencyM(g, v.vertex);

		// para cada adjacente do vertice
		for (i = 0; adj[i] != NoEdge; i++){
			// caso ele nao esteja na MST e o custo da ligacao entre os dois seja a menor
			if (!addCheck[adj[i]] && getEdgeCostM(g, v.vertex, adj[i]) < heapGetCost(Q, adj[i])){
				// atualize sua prioridade
				heapUpdate(Q, adj[i], getEdgeCostM(g, v.vertex, adj[i]));

				// atualize seu predecessor
				pred[adj[i]] = v.vertex;
			}
		}

		// liberando memoria auxiliar
		free(adj);
	}

	// liberando memoria auxiliar
	heapDestroy(Q);
	free(addCheck);

	// retornando valores
	*MSTorder = order;
	return pred;

}