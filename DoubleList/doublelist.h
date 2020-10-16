#ifndef _DOUBLELIST_H_
#define _DOUBLELIST_H_

typedef struct ListNode ListNode;
typedef struct List List;
typedef struct ListItem ListItem;

struct ListItem {
	int key;
	int value;
};

struct ListNode {
	ListItem *item;
	ListNode *next;
	ListNode *prev;
};

struct List {
	ListNode *first;
	ListNode *last;
	int size;
};

List *listCreate();
void listFree(List *list);

ListItem *listCreateItem(int key, int value);

int listGetSize(List *list);
int listIsEmpty(List *list);

void listInsert(List *list, ListItem *it);
void listRemove(List *list, int key);
ListItem *listSearch (List *list, int key);

void listPrintNode(ListNode *n);
void listPrint(List *list);

#endif