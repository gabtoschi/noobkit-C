#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "mgraph.h"
#include "utils.h"

struct MGraph {
	int n;
	int **vertices;
	bool isDigraph;
};

int getVerticesQuantM(MGraph *g){
	return g->n;
}

MGraph *createGraphM(int n, bool digraph){
	int i, j;

	// alocando grafo
	MGraph *g = (MGraph *) malloc(sizeof(MGraph));

	// inserindo informacoes do grafo
	g->n = n;
	g->isDigraph = digraph;

	// alocando matriz
	g->vertices = (int **) malloc(sizeof(int *) * n);
	for (i = 0; i < n; i++){
		g->vertices[i] = (int *) malloc(sizeof(int) * n);
		for (j = 0; j < n; j++){
			g->vertices[i][j] = NoEdge;
		}
	}

	return g;
}

int insertEdgeM(MGraph *g, int v1, int v2, int value){
	// checa se os vertices existem
	if (v1 < 0 || v1 >= g->n || v2 < 0 || v2 >= g->n){
		// vertice nao existe, retorne erro
		return -1;
	}

	// criando aresta entre V1 -> V2
	g->vertices[v1][v2] = value;

	// verificando se nao eh um digrafo
	if (!g->isDigraph){
		// caso nao seja digrafo, crie aresta entre V2 -> V1
		g->vertices[v2][v1] = value;
	}

	return 0;
}

int removeEdgeM(MGraph *g, int v1, int v2){
	// checa se os vertices existem
	if (v1 < 0 || v1 >= g->n || v2 < 0 || v2 >= g->n){
		// vertice nao existe, retorne erro
		return -1;
	}

	// removendo aresta entre V1 -> V2;
	g->vertices[v1][v2] = NoEdge;

	// verificando se nao eh um digrafo
	if (!g->isDigraph){
		// caso nao seja digrafo, remova aresta entre V2 -> V1
		g->vertices[v2][v1] = NoEdge;
	}

	return 0;
}

void printGraphM(MGraph *g){
	int i, j, n;
	n = g->n;

	// percorre a matriz
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			// caso nao exista aresta
			if (g->vertices[i][j] == NoEdge){
				// imprima vazio
				printf(". ");
			} else {
				// imprima o valor
				printf("%d ", g->vertices[i][j]);
			}
		}

		printf("\n");
	}
}

void transposeGraphM(MGraph *g){
	int i, j, n;
	n = g->n;

	// percorre a matriz
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			// caso nao exista aresta
			if (g->vertices[j][i] == NoEdge){
				// imprima vazio
				printf(". ");
			} else {
				// imprima o valor
				printf("%d ", g->vertices[j][i]);
			}
		}

		printf("\n");
	}
}

int *getAdjacencyAscM(MGraph *g, int v){
	int i;
	int adjCounter = 0;
	int *adj = NULL;

	// fixa na linha da matriz e percorre-a, procurando arestas
	for (i = 0; i < g->n; i++){
		// caso exista aresta, armazene o numero da aresta
		if (g->vertices[v][i] != NoEdge){
			adj = (int *) realloc(adj, sizeof(int) * (adjCounter + 1));
			adj[adjCounter++] = i;
		}
	}

	adj = (int *) realloc(adj, sizeof(int) * (adjCounter + 1));
	adj[adjCounter++] = NoEdge;

	return adj;
}

int *getAdjacencyDescM(MGraph *g, int v){
	int i;
	int adjCounter = 0;
	int *adj = NULL;

	// fixa na linha da matriz e percorre-a, procurando arestas
	for (i = g->n - 1; i >= 0; i--){
		// caso exista aresta, armazene o numero da aresta
		if (g->vertices[v][i] != NoEdge){
			adj = (int *) realloc(adj, sizeof(int) * (adjCounter + 1));
			adj[adjCounter++] = i;
		}
	}

	adj = (int *) realloc(adj, sizeof(int) * (adjCounter + 1));
	adj[adjCounter++] = NoEdge;

	return adj;
}

void getLowerM(MGraph *g){
	int i, j;
	int v1, v2, lower = INT_MAX;

	// percorre a matriz
	for (i = 0; i < g->n; i++){
		for (j = 0; j < g->n; j++){
			// caso exista a aresta e tenha o menor peso
			if (g->vertices[i][j] != NoEdge && g->vertices[i][j] < lower){
				v1 = i;
				v2 = j;
				lower = g->vertices[i][j];
			}
		}
	}

	// formata saida, caso nao seja um digrafo
	if (!g->isDigraph && v1 > v2){
		i = v2;
		v2 = v1;
		v1 = i;
	}

	printf("%d %d\n", v1, v2);
}

void destroyGraphM(MGraph *g){
	// liberar matriz da memoria heap
	int i;

	for (i = 0; i < g->n; i++){
		free(g->vertices[i]);
	}

	free(g->vertices);

	// liberando grafo da memoria heap
	free(g);
}