#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Graph.h"

#define MAXC 30
#define maxWT INT_MAX

typedef struct node *link;
struct node {
    int v;
    int wt;
    link next;
};

struct graph {
    int V;
    int E;
    int **madj;
    ST tab;
    link *ladj;
    link z;
};

static link NEW(int v, int wt, link next);

static Edge EDGEcreate(int v, int w, int wt);

static int **MATRIXint(int r, int c, int val);

static void insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    if (t == NULL)
        return NULL;

    for (i = 0; i < r; i++) {
        t[i] = malloc(c * sizeof(int));
        if (t[i] == NULL)
            return NULL;
    }
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    if (G == NULL)
        return NULL;
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, maxWT);
    if (G->madj == NULL)
        return NULL;
    G->tab = STinit(V);
    if (G->tab == NULL)
        return NULL;
    return G;
}

void GRAPHfree(Graph G) {
    int i;
    link t, next;
    if (G->ladj != NULL)
        for (i = 0; i < G->V; i++)
            for (t = G->ladj[i]; t != G->z; t = next) {
                next = t->next;
                free(t);
            }
    for (i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);
    STfree(G->tab);
    free(G->ladj);
    free(G->z);
    free(G);
}

Graph GRAPHload(FILE *fin) {
    int V = 0, i = 0, id1, id2, wt;
    char label1[MAXC], label2[MAXC], network_id1[MAXC], network_id2[MAXC], temp[140];
    Graph G;

    while (fscanf(fin, "%s %s %s %s %d", label1, network_id1, label2, network_id2, &wt) != EOF)
        V++;
    G = GRAPHinit(V);
    rewind(fin);

    while (fgets(temp, 130, fin) != NULL) {
        sscanf(temp, "%s %s %s %s %d", label1, network_id1, label2, network_id2, &wt);
        if (STsearch(G->tab, label1) == -1)
            STinsert(G->tab, label1, network_id1, i++);
        if (STsearch(G->tab, label2) == -1)
            STinsert(G->tab, label2, network_id2, i++);
    }
    G->V = i;
    rewind(fin);

    while (fscanf(fin, "%s %s %s %s %d", label1, network_id1, label2, network_id2, &wt) == 5) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >= 0)
            GRAPHinsertE(G, id1, id2, wt);
    }

    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == maxWT)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void listGRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v = 0; v < G->V; v++)
        for (t = G->ladj[v]; t != G->z; t = t->next)
            if (v < t->v)
                a[E++] = EDGEcreate(v, t->v, t->wt);
}

void GRAPHedges(Graph G, Edge *a) {
    int v, w, E = 0;
    for (v = 0; v < G->V; v++)
        for (w = v + 1; w < G->V; w++)
            if (G->madj[v][w] != maxWT)
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void GRAPHstore(Graph G, FILE *fout, int flag) {
    int i, j;
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
        return;

    if (flag)
        listGRAPHedges(G, a);
    else
        GRAPHedges(G, a);

    fprintf(fout, "Numero vertici: %d", G->V);
    for (i = 0; i < G->V; i++) {
        fprintf(fout, "\n%s || ", STsearchByIndex(G->tab, i));
        fprintf(fout, "Archi: ");
        for (j = 0; j < G->E; j++)
            if (a[j].v == i || a[j].w == i) {
                fprintf(fout, "%s  %s %d |", STsearchByIndex(G->tab, a[j].v), STsearchByIndex(G->tab, a[j].w), a[j].wt);
            }
    }
}

int GRAPHgetIndex(Graph G, char *label) {
    int id;
    id = STsearch(G->tab, label);
    if (id == -1) {
        id = STsize(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

int GRAPHadjacent(Graph G, char *vertex1, char *vertex2, char *vertex3) {
    int index1, index2, index3;
    index1 = STsearch(G->tab, vertex1);
    index2 = STsearch(G->tab, vertex2);
    index3 = STsearch(G->tab, vertex3);
    if (index1 == -1 || index2 == -1 || index3 == -1) {
        printf("Vertice/i non trovato/i\n");
        return 0;
    }
    if (G->madj[index1][index2] != 0) {
        if (G->madj[index1][index3] != 0)
            if (G->madj[index2][index3] != 0)
                return 1;
    }
    return 0;
}

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}

int GRAPHmat2list(Graph G) {
    int v, i, j;
    G->z = NEW(-1, 0, NULL);
    if (G->z == NULL)
        return 0;
    G->ladj = malloc(G->V * sizeof(link));
    if (G->ladj == NULL)
        return 0;
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;

    for (i = 1; i < G->V; i++) {
        for (j = 0; j < i; j++)
            if (G->madj[i][j] != maxWT) {
                G->ladj[i] = NEW(j, G->madj[i][j], G->ladj[i]);
                G->ladj[j] = NEW(i, G->madj[i][j], G->ladj[j]);
                if (G->ladj[i] == NULL || G->ladj[j] == NULL)
                    return 0;
            }
    }
    return 1;
}