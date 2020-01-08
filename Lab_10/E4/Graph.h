#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);

void GRAPHfree(Graph G);

Graph GRAPHload(FILE *);

void GRAPHinsertE(Graph G, int id1, int id2, int wt);

void GRAPHstore(Graph G, FILE *fout, int flag);

int GRAPHgetIndex(Graph G, char *label);

void GRAPHedges(Graph G, Edge *a);

int GRAPHadjacent(Graph G, char *vertex1, char *vertex2, char *vertex3);

int GRAPHmat2list(Graph G);

#endif
