#include <stdlib.h>
#include <stdio.h>

#include "BFS.h"
#include "mgraph.h"
#include "queue.h"

typedef enum {
	WHITE = 0,
	GRAY,
	BLACK
} Color;

int *BFS(MGraph *graph, int q){
	int i, u;
	int n = getVerticesQuantM(graph);
	int *adj;

	// criando vetor de cores
	Color *color = (Color *) calloc(n, sizeof(Color));

	// criando vetor de predecessores
	int *tree = (int *) malloc(n * sizeof(int));
	for (i = 0; i < n; i++) tree[i] = nil;

	// criando vetor de distancias
	int *d = (int *) calloc(n, sizeof(int));

	// criando lista de navegacao
	Queue *nav = queueCreate(n);

	// prepara o primeiro vertice
	queuePush(nav, q);
	color[q] = GRAY;

	// enquanto a lista de navegacao nao estiver vazia
	while (!queueEmpty(nav)){

		// pegue o topo da lista
		u = queuePop(nav);

		// pegue os vertices adjacentes a u
		adj = getAdjacencyAscM(graph, u);

		// percorra os adjacentes
		for (i = 0; adj[i] != NoEdge; i++){

			// caso o adjacente esteja branco
			if (color[adj[i]] == WHITE){
				// atualize sua cor
				color[adj[i]] = GRAY;

				// atualize sua distancia
				d[adj[i]]++;

				// atualize seu predecessor
				tree[adj[i]] = u;

				// coloque-o na lista de navegacao
				queuePush(nav, adj[i]);
			}
		}

		// atualize a cor do no atual
		color[u] = BLACK;

		// desalocando vetor de adjacencias
		free(adj);
	}

	// desalocando vetores auxiliares
	free(color);
	free(d);
	queueDestroy(nav);

	return tree;

}