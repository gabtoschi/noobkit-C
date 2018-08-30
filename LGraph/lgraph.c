#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "lgraph.h"
#include "utils.h"
#include "simplelist.h"

struct LGraph {
	int n;
	bool isDigraph;
	List **vertices;
};

LGraph *createGraphL(int n, bool digraph){
	int i;

	// alocando grafo
	LGraph *g = (LGraph *) malloc(sizeof(LGraph));

	// inserindo informacoes do grafo
	g->n = n;
	g->isDigraph = digraph;

	// alocando listas de adjacencias
	g->vertices = (List **) malloc(sizeof(List *) * n);

	for (i = 0; i < n; i++){
		g->vertices[i] = listCreate();
	}

	return g;
}

int insertEdgeL(LGraph *g, int v1, int v2, int value){
	// checa se os vertices existem
	if (v1 < 0 || v1 >= g->n || v2 < 0 || v2 >= g->n){
		// vertice nao existe, retorne erro
		return -1;
	}

	// verifica se a aresta ja existe
	ListItem *exist = listSearch(g->vertices[v1], v2);
	if (exist != NULL){
		// atualiza a aresta
		exist->value = value;
	} else {
		// criando aresta entre V1 -> V2
		listInsert(g->vertices[v1], listCreateItem(v2, value));
	}

	// verificando se nao eh um digrafo ou esta ligado no proprio vertice
	if (!g->isDigraph && v1 != v2){
		// caso a aresta ja exista
		if (exist != NULL){
			// procura na outra lista
			ListItem *exist = listSearch(g->vertices[v2], v1);

			// atualiza a aresta
			exist->value = value;
		} else {
			// caso nao exista, crie aresta entre V2 -> V1
			listInsert(g->vertices[v2], listCreateItem(v1, value));
		}
	}
}

int removeEdgeL(LGraph *g, int v1, int v2){
	// checa se os vertices existem
	if (v1 < 0 || v1 >= g->n || v2 < 0 || v2 >= g->n){
		// vertice nao existe, retorne erro
		return -1;
	}

	// removendo aresta entre V1 -> V2;
	listRemove(g->vertices[v1], v2);

	// verificando se nao eh um digrafo
	if (!g->isDigraph){
		// caso nao seja digrafo, remova aresta entre V2 -> V1
		listRemove(g->vertices[v2], v1);
	}

	return 0;
}

void printGraphL(LGraph *g){
	int i;

	// percorra pelos vertices
	for (i = 0; i < g->n; i++){
		printf("%d. ", i);
		// imprima a lista de cada vertice
		listPrint(g->vertices[i]);
		printf("\n");
	}
}

void transposeGraphL(LGraph *g){
	int i, j;
	ListNode *nodeAux;

	// criar matriz auxiliar para transposicao
	int **aux = (int **) malloc(sizeof(int *) * g->n);
	for (i = 0; i < g->n; i++){
		// criar linha da matriz
		aux[i] = (int *) malloc(sizeof(int) * g->n);

		// preencher linha da matriz com valores da lista i
		nodeAux = g->vertices[i]->first;

		for (j = 0; j < g->n; j++){
			// caso o proximo da lista seja a posicao desejada da matriz
			if (nodeAux != NULL && nodeAux->item->vertex == j){
				aux[i][j] = nodeAux->item->value;
				nodeAux = nodeAux->next;
			} else {
				// indique que nao tem arestas
				aux[i][j] = -1;
			}
		}
	}

	// imprimir matriz de forma transposta
	for (j = 0; j < g->n; j++){
		printf("%d. ", j);
		for (i = 0; i < g->n; i++){
			// caso exista vertice, imprima
			if (aux[i][j] != -1){
				printf("%d(%d) ", i, aux[i][j]);
			}
		}

		printf("\n");
	}

	// liberar matriz
	for (i = 0; i < g->n; i++){
		free(aux[i]);
	}
	free(aux);

}

void getAdjacencyL(LGraph *g, int v){
	// fixa em uma das listas de adjacencia
	ListNode *l = g->vertices[v]->first;

	// percorre ate o fim da lista, imprimindo os vertices
	while (l != NULL){
		printf("%d ", l->item->vertex);
		l = l->next;
	}

	printf("\n");
}

void getLowerL(LGraph *g){
	int i;
	ListNode *j;
	int v1, v2, lower = INT_MAX;

	// percorre todas as listas de adjacencias
	for (i = 0; i < g->n; i++){
		j = g->vertices[i]->first;

		// percorre a lista ate o final
		while (j != NULL){
			// se esse for o menor peso ate agora, salve
			if (j->item->value < lower){
				v1 = i;
				v2 = j->item->vertex;
				lower = j->item->value;
			}

			j = j->next;
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

void destroyGraphL(LGraph *g){
	// liberar listas de adjacencias da memoria heap
	int i;

	for (i = 0; i < g->n; i++){
		listFree(g->vertices[i]);
	}

	free(g->vertices);

	// liberar grafo da memoria heap
	free(g);
}
