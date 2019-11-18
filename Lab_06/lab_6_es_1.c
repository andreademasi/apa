//
// Created by Andrea De Masi on 17/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int u;
    int v;
} Arc;

typedef struct {
    int *vertices;
    Arc *arches;
} Graph;

Graph openFile(int *vertices_number, int *arches_number);

int powerset(int pos, int *val, int *sol, int k, int start, int count, int arches_number, Arc *arches);

int main() {
    int vertices_number, arches_number;

    Graph graph = openFile(&vertices_number, &arches_number);

    int *sol = malloc(pow(2, vertices_number) * sizeof(int));

    powerset(0, graph.vertices, sol, vertices_number, 0, 0, arches_number, graph.arches);
}

Graph openFile(int *vertices_number, int *arches_number) {
    Graph graph;
    int i = 0, j, k = 0, found = 0;

    FILE *fp = fopen("/home/andrea/apa/Lab_06/es1.txt", "r");

    fscanf(fp, "%d %d", vertices_number, arches_number);

    graph.vertices = malloc(*vertices_number * sizeof(int));
    graph.arches = malloc(*arches_number * sizeof(Arc));

    for (j = 0; j < *vertices_number; j++)
        graph.vertices[j] = -1;

    while (fscanf(fp, "%d %d", &graph.arches[i].u, &graph.arches[i].v) != EOF) {
        for (j = 0; j <= k; j++) {
            if (graph.vertices[j] == graph.arches[i].u)
                found = 1;
        }
        if (found == 0) {
            graph.vertices[k] = graph.arches[i].u;
            k++;
        }
        found = 0;
        for (j = 0; j <= k; j++) {
            if (graph.vertices[j] == graph.arches[i].v)
                found = 1;
        }
        if (found == 0) {
            graph.vertices[k] = graph.arches[i].v;
            k++;
        }
        found = 0;
        i++;
    }

    return graph;
}

int powerset(int pos, int *val, int *sol, int k, int start, int count, int arches_number, Arc *arches) {
    int i, j, found = 0;
    if (start >= k) {
        for (j = 0; j < arches_number; j++) {
            found = 0;
            for (i = 0; i < pos; i++) {
                if (sol[i] == arches[j].u || sol[i] == arches[j].v)
                    found = 1;
            }
            if (found == 0)
                break;
        }
        if (found > 0 && pos != 1) {
            for (i = 0; i < pos; i++)
                printf("%d ", sol[i]);
            printf("\n");
        }
        return count + 1;
    }
    for (i = start; i < k; i++) {
        sol[pos] = val[i];
        count = powerset(pos + 1, val, sol, k, i + 1, count, arches_number, arches);
    }
    count = powerset(pos, val, sol, k, k, count, arches_number, arches);
    return count;
}

