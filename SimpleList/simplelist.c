/**
	>>>> SIMPLELIST <<<<
	Estruturas e funcoes para uso
	de listas ligadas.
**/

#include "simplelist.h"

#include <stdlib.h>
#include <stdio.h>

/** >> listCreate
	Inicializa uma lista.
**/
List *listCreate(){
	List *l = (List *) malloc(sizeof(List));
	l->first = NULL;
	l->size = 0;
	
	return l;
}

/** >> listCreateNode
	Inicializa um no de lista a
	partir de um item.
**/
ListNode *listCreateNode(ListItem *it){
	ListNode *n = (ListNode *) malloc(sizeof(ListNode));
	n->next = NULL;
	n->item = it;
	
	return n;
}

/** >> listCreateItem
	Inicializa um item de lista a
	partir de dados.
**/
ListItem *listCreateItem(int vertex, int value){
	ListItem *n = (ListItem *) malloc(sizeof(ListItem));
	n->vertex = vertex;
	n->value = value;
	
	return n;
}

/** >> listGetSize
	Retorna o tamanho de uma lista.
**/
int listGetSize(List *list){
	return list->size;
}

/** >> listIsEmpty
	Retorna 1 se a lista estiver vazia.
**/
int listIsEmpty(List *list){
	if (list->size == 0) return 1;
	return 0;
}

/** >> listPrintNode
	Imprime um no de lista na saida padrao.
**/
void listPrintNode(ListNode *n){
	printf("%d(%d) ", n->item->vertex, n->item->value);
}

/** >> _listPrint
	Imprime recursivamente uma lista.
**/
void _listPrint(ListNode *n){
	if (n == NULL) return;
	listPrintNode(n);
	_listPrint(n->next);
}

/** >> listPrint
	Inicia o processo recursivo de impressao
	de uma lista.
**/
void listPrint(List *list){
	_listPrint(list->first);
}

/** >> listCheckItem
	Faz a checagem entre dois itens para a insercao
	ordenada, chamando a funcao correta para tal.
**/
int listCheckItem(ListItem *a, ListItem *b){
	if (a->vertex < b->vertex) return -1;
	if (a->vertex == b->vertex) return 0;
	return 1;
}

/** >> listInsert
	Insere um novo elemento na lista de forma
	ordenada.
**/
void listInsert(List *list, ListItem *it){
	ListNode *new, *p = list->first, *pant;

	while (p != NULL){
		if (listCheckItem(p->item, it) < 0){
			pant = p;
			p = p->next;
		}
		else break;
	}
	
	new = listCreateNode(it);
	list->size++;
	
	if (list->size == 1){ // esse e' o primeiro no da lista
		list->first = new;
		return;
	} 
	
	if (p == list->first){ // novo item deve ser colocado no começo da lista
		new->next = list->first;
		list->first = new;
		return;
	}
	
	if (p == NULL){ // novo item deve ser colocado ao final da lista
		pant->next = new;
		return; 
	}
	
	// novo item deve ser colocado no meio da lista
	pant->next = new;
	new->next = p;
	return;
}

/** >> listRemove
	Remove um no da lista.
**/
void listRemove(List *list, int queue){
	ListNode *p = list->first, *pant;
	ListItem *queueItem = listCreateItem(queue, 0);
	
	while (p != NULL){
		if (listCheckItem(p->item, queueItem) == 0)
			break;
		else {
			pant = p;
			p = p->next;
		}
	}

	if (p == NULL){// no a ser removido nao foi encontrado
		free(queueItem);
		return;
	}

	if (p == list->first){ // remover primeiro no da lista
		list->first = p->next;
	} else {
		pant->next = p->next;
	}
		
	list->size--;
	free(p->item);
	free(p);
	free(queueItem);
}

/** >> listSearch
	Procura um determinado item na
	lista e o retorna. Caso nao seja
	encontrado, retorna NULL.
**/

ListItem *listSearch (List *list, int queue){
	ListNode *p = list->first, *pant;
	ListItem *queueItem = listCreateItem(queue, 0);

	while (p != NULL){
		if (listCheckItem(p->item, queueItem) == 0)
			break;
		else {
			pant = p;
			p = p->next;
		}
	}

	free(queueItem);
	if (p == NULL) return NULL;
	return p->item;
}

/** >> listFree
	Remove todos os nos de uma lista
	e a libera da memoria Heap.
**/
void listFree(List *list){
	ListNode *p = list->first;
	ListNode *paux;

	while (p != NULL){
		paux = p->next;
		free(p->item);
		free(p);
		p = paux;
	}

	free(list);
}

