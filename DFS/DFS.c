#include <stdlib.h>
#include <stdio.h>

#include "DFS.h"
#include "mgraph.h"

typedef enum {
	WHITE = 0,
	GRAY,
	BLACK
} Color;

void DFSvisit(MGraph *graph, int v, Color *color, int* tree, int *d, int *f, int* time){
	int i;

	// pinte de cinza o vertice visitado
	color[v] = GRAY;

	// atualize o primeiro timestamp
	d[v] = ++(*time);

	// pegue os vertices adjacentes do vertice
	int* adj = getAdjacencyM(graph, v);

	// percorra os adjacentes
	for (i = 0; adj[i] != NoEdge; i++){
		// caso o adjacente esteja branco
		if (color[adj[i]] == WHITE){
			// atualize seu predecessor
			tree[adj[i]] = v;

			// visite o vertice
			DFSvisit(graph, adj[i], color, tree, d, f, time);
		}
	}

	// pinte de preto o vertice completo
	color[v] = BLACK;

	// atualize o segundo timestamp
	f[v] = ++(*time);

	// desalocando memoria auxiliar
	free(adj);
}

int *DFS(MGraph *graph, int q){
	int i;
	int time = 0;
	int n = getVerticesQuantM(graph);

	// criando vetor de cores
	Color *color = (Color *) calloc(n, sizeof(Color));

	// criando vetor de predecessores
	int *tree = (int *) malloc(n * sizeof(int));
	for (i = 0; i < n; i++) tree[i] = nil;

	// criando vetores para timestamps
	int *d = (int *) calloc(n, sizeof(int));
	int *f = (int *) calloc(n, sizeof(int));

	// comece a percorrer o grafo a partir do vertice de saida
	DFSvisit(graph, q, color, tree, d, f, &time);

	// desalocando vetores auxiliares
	free(color);
	free(d);
	free(f);

	return tree;
}	