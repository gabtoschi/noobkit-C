#ifndef _LGRAPH_H_
#define _LGRAPH_H_

#include "utils.h"

typedef struct LGraph LGraph;

LGraph *createGraphL(int n, bool digraph);
int insertEdgeL(LGraph *g, int v1, int v2, int value);
int removeEdgeL(LGraph *g, int v1, int v2);
void printGraphL(LGraph *g);
void transposeGraphL(LGraph *g);
void getAdjacencyL(LGraph *g, int v);
void getLowerL(LGraph *g);
void destroyGraphL(LGraph *g);

#endif

