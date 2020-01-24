#include <stdlib.h>
#include <stdio.h>

#include "titolo_collection.h"
#include "titolo.h"

typedef struct node_struct {
    struct node_struct *next;
    Titolo t;
} node;

typedef node *link;

struct titoli_collection_struct {
    link head;
    int count;
};

titoli_collection Init_TitoliCollection() {
    titoli_collection titoli = calloc(1, sizeof *titoli);
    return titoli;
}

int Empty_TitoliCollection(titoli_collection titoli) {
    if (titoli == NULL || titoli->head == NULL || titoli->count == 0)
        return 1;
    return 0;
}

Titolo Search_TitoliCollection(titoli_collection titoli, char *cod) {
    int cmp;
    link x;
    if (Empty_TitoliCollection(titoli))
        return NULL;
    for (x = titoli->head; x != NULL; x = x->next) {
        cmp = TITOLOcmp((Key) cod, TITOLOgetKey(x->t));
        if (cmp == 0)
            return x->t;
        if (cmp < 0)
            return NULL;
    }
    return NULL;
}

static link NEW(Titolo t, link next) {
    link l = calloc(1, sizeof *l);
    l->t = t;
    l->next = next;
    return l;
}

void Insert_TitoliCollection(titoli_collection titoli, Titolo t) {
    link x, p;
    if (titoli == NULL)
        return;
    if (titoli->head == NULL) {
        titoli->head = NEW(t, NULL);
    } else if (TITOLOcmp(TITOLOgetKey(t), TITOLOgetKey(titoli->head->t)) < 0) {
        titoli->head = NEW(t, titoli->head);
    } else {
        for (x = titoli->head->next, p = titoli->head;
             x != NULL && TITOLOcmp(TITOLOgetKey(t), TITOLOgetKey(x->t)) > 0; p = x, x = x->next);
        p->next = NEW(t, x);
    }
    titoli->count++;
}
