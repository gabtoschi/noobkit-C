#ifndef _MGRAPH_H_
#define _MGRAPH_H_

#include "utils.h"

#define NoEdge -1

typedef struct MGraph MGraph;

int getVerticesQuantM(MGraph *g);
MGraph *createGraphM(int n, bool digraph);
int insertEdgeM(MGraph *g, int v1, int v2, int value);
int removeEdgeM(MGraph *g, int v1, int v2);
void printGraphM(MGraph *g);
void transposeGraphM(MGraph *g);
int *getAdjacencyAscM(MGraph *g, int v);
int *getAdjacencyDescM(MGraph *g, int v);
void getLowerM(MGraph *g);
void destroyGraphM(MGraph *g);

#endif