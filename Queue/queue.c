#include <stdlib.h>
#include <stdio.h>

#include <utils.h>
#include <queue.h>

struct Queue {
	int *data;
	int max;
	int start;
	int end;
	int size;
};

Queue *queueCreate(int maxSize){
	// alocando nova lista
	Queue *new = (Queue *) malloc(sizeof(Queue));

	// alocando vetor de dados da pilha
	new->data = (int *) malloc(sizeof(int) * maxSize);

	// atribuindo maximos e inicializando
	new->max = maxSize;
	new->size = 0;
	new->start = -1;
	new->end = -1;

	return new;
}

bool queueEmpty(Queue *q){
	// retorna false se a lista estiver vazia
	return q->size == 0 ? true : false;
}

bool queueFull(Queue *q){
	// retorna false se a lista estiver cheia
	return q->size == q->max ? true : false;
}

int modPlus1(int i, int b){
	// adiciona 1 na variavel de forma circular, com mod
	return (i + 1) % b;
}

void queuePush(Queue *q, int d){
	// caso a lista nao esteja cheia
	if (!queueFull(q)){
		// se for o começo da lista
		if (queueEmpty(q)){
			q->start = 0;
			q->end = 0;
		} else {
			q->end = modPlus1(q->end, q->max);
		}

		q->data[q->end] = d;
		q->size++;
	}
}

int queuePop(Queue *q){
	int r = -1;

	if (!queueEmpty(q)){
		r = q->data[q->start];

		if (q->size == 1){
			q->start = -1;
			q->end = -1;
		} else {
			q->start = modPlus1(q->start, q->max);
		}

		q->size--;
	}

	return r;
}

int queueView(Queue *q){
	// caso a lista nao esteja vazia
	if (!queueEmpty(q))
		// recupere o começo da lista
		return q->data[q->start];

	return -1;
}

void queueDestroy(Queue *q){
	// libera o vetor de dados
	free(q->data);

	// libera a lista
	free(q);
}