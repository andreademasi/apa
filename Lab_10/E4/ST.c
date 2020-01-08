#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symboltable {
    char **a;
    char **network_id;
    int maxN;
    int N;
};


ST STinit(int maxN) {
    ST st;
    st = malloc(sizeof(*st));
    if (st == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }
    st->a = calloc(maxN, sizeof(char *));
    if (st->a == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    st->network_id = calloc(maxN, sizeof(char *));
    if (st->network_id == NULL) {
        printf("Memory allocation error\n");
        free(st);
        return NULL;
    }
    st->maxN = maxN;
    st->N = 0;
    return st;
}

void STfree(ST st) {
    int i;
    if (st == NULL)
        return;
    for (i = 0; i < st->N; i++)
        if (st->a[i] != NULL) {
            free(st->a[i]);
            free(st->network_id[i]);
        }
    free(st->a);
    free(st);
}

int STsize(ST st) {
    return st->N;
}

void STinsert(ST st, char *str, char *network_id, int i) {
    if (i >= st->maxN) {
        st->a = realloc(st->a, (2 * st->maxN) * sizeof(char *));
        if (st->a == NULL)
            return;
        st->maxN = 2 * st->maxN;
    }
    while ((i > 0) && strcmp(str, st->a[i - 1]) < 0) {
        st->a[i] = st->a[i - 1];
        i--;
    }
    st->a[i] = strdup(str);
    st->network_id[i] = strdup(network_id);
    st->N++;
}

static int searchR(ST st, int l, int r, char *k) {
    int m = (l + r) / 2;
    if (l > r)
        return -1;
    if (strcmp(k, st->a[m]) == 0)
        return m;
    if (l == r)
        return -1;
    if (strcmp(k, st->a[m]) < 0)
        return searchR(st, l, m - 1, k);
    else
        return searchR(st, m + 1, r, k);
}

int STsearch(ST st, char *str) {
    return searchR(st, 0, st->N - 1, str);
}

char *STsearchByIndex(ST st, int i) {
    if (i < 0 || i >= st->N)
        return NULL;
    return (st->a[i]);
}

