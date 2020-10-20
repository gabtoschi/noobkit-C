#include "doublelist.h"

#include <stdlib.h>
#include <stdio.h>

/** >> listCreate
	Inicializa uma lista.
**/
List *listCreate(){
	List *l = malloc(sizeof(List));
	l->first = NULL;
	l->last = NULL;
	l->size = 0;

	return l;
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

/** >> listCreateItem
	Inicializa um item de lista a
	partir de dados.
**/
ListItem *listCreateItem(int key, int value){
	ListItem *n = malloc(sizeof(ListItem));
	n->key = key;
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
	return list->size == 0 ? 1 : 0;
}

/** >> _listCheckItem
	Faz a checagem entre dois itens para a insercao
	ordenada, chamando a funcao correta para tal.
**/
int _listCheckItem(ListItem *a, ListItem *b){
	if (a->key < b->key) return -1;
	if (a->key == b->key) return 0;
	return 1;
}

/** >> _listCreateNode
	Inicializa um no de lista a
	partir de um item.
**/
ListNode *_listCreateNode(ListItem *it){
	ListNode *n = malloc(sizeof(ListNode));
	n->next = NULL;
	n->prev = NULL;
	n->item = it;
	return n;
}

/** >> listInsert
	Insere um novo elemento na lista de forma
	ordenada.
**/
int A = 1;
void listInsert(List *list, ListItem *it){
	ListNode *p = list->first;

	A = 1;
	while (p != NULL){
		printf("%d ", A++);
		if (_listCheckItem(p->item, it) > 0) break;
		p = p->next;
	}
	printf("\n");

	ListNode *new = _listCreateNode(it);
	list->size++;

	if (list->size == 1){ // esse e' o primeiro no da lista
		list->first = new;
		list->last = new;
		return;
	}

	if (p == list->first){ // novo item deve ser colocado no começo da lista
		printf("to aqui oh ");
		listPrintNode(new);
		printf("\n");
		list->first->prev = new;
		new->next = list->first;
		list->first = new;
		return;
	}

	if (p == NULL){ // novo item deve ser colocado ao final da lista
		list->last->next = new;
		new->prev = list->last;
		list->last = new;
		return; 
	}

	// novo item deve ser colocado no meio da lista
	p->prev->next = new;
	new->prev = p->prev;
	p->prev = new;
	new->next = p;
	return;
}

/** >> listRemove
	Remove um no da lista.
**/
void listRemove(List *list, int key){
	ListNode *p = list->first;
	ListItem *queueItem = listCreateItem(key, 0);
	
	while (p != NULL){
		if (_listCheckItem(p->item, queueItem) == 0) break;
		p = p->next;
	}

	if (p == NULL){// no a ser removido nao foi encontrado
		free(queueItem);
		return;
	}

	if (p == list->first){ // remover primeiro no da lista
		list->first = p->next;
		list->first->prev = NULL;
	} else if (p == list->last){ // remover o últio no da lista
		list->last = p->prev;
		list->last->next = NULL;
	} else {
		p->prev->next = p->next;
		p->next->prev = p->prev;
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
ListItem *listSearch (List *list, int key){
	ListNode *p = list->first;
	ListItem *queueItem = listCreateItem(key, 0);

	while (p != NULL){
		if (_listCheckItem(p->item, queueItem) == 0) break;
		p = p->next;
	}

	free(queueItem);
	if (p == NULL) return NULL;
	return p->item;
}

/** >> listPrintNode
	Imprime um no de lista na saida padrao.
**/
void listPrintNode(ListNode *n){
	printf("(%d): %d ", n->item->key, n->item->value);
}

/** >> listPrint
	Imprime toda lista.
**/
void listPrint(List *list, int mode){
	ListNode *p = list->first;

	printf("[ ");
	while (p != NULL) {
		listPrintNode(p);
		p = p->next;
	}
	printf("]\n");
}