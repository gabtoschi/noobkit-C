/**
	>>>> SIMPLELIST <<<<
	Estruturas e funcoes para uso
	de listas ligadas.
**/

#ifndef _SIMPLELIST_H_
#define _SIMPLELIST_H_

typedef struct ListNode ListNode;
typedef struct List List;
typedef struct ListItem ListItem;

struct ListItem {
	int vertex;
	int value;
};

struct ListNode {
	ListItem *item;
	ListNode *next;
};

struct List {
	ListNode *first;
	int size;
};

List *listCreate();
ListNode *listCreateNode(ListItem *it);
ListItem *listCreateItem(int vertex, int value);
int listGetSize(List *list);
int listIsEmpty(List *list);
void listPrintNode(ListNode *n);
void listPrint(List *list);
void listInsert(List *list, ListItem *it);
void listRemove(List *list, int queue);
ListItem *listSearch (List *list, int queue);
void listFree(List *list);

#endif
