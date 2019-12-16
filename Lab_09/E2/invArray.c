//
// Created by Andrea on 16/12/2019.
//

#include "invArray.h"
#include "equipArray.h"
#include "pg.h"

struct invArray_s {
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

invArray_t invArray_init() {
    invArray_t t = malloc(sizeof(*t));
    t->maxInv = 0;
    t->nInv = 0;
    return t;
}

void invArray_free(invArray_t invArray) {
    free(invArray->vettInv);
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray) {
    int i = 0;
    fscanf(fp, "%d", &invArray->nInv);

    invArray->vettInv = malloc(invArray->nInv * sizeof(inv_t));

    while (fscanf(fp, "%s %s %d %d %d %d %d %d", invArray->vettInv[i].nome, invArray->vettInv[i].tipo,
                  &invArray->vettInv[i].stat.hp, &invArray->vettInv[i].stat.mp, &invArray->vettInv[i].stat.atk,
                  &invArray->vettInv[i].stat.def, &invArray->vettInv[i].stat.mag, &invArray->vettInv[i].stat.spr) !=
           EOF)
        i++;
}

void invArray_print(FILE *fp, invArray_t invArray) {
    int i;
    printf("\nInventario disponibile:\n");
    for (i = 0; i < invArray->nInv; i++)
        inv_print(fp, &invArray->vettInv[i]);
}

int invArray_searchByName(invArray_t invArray, char *name) {
    int i;
    for (i = 0; i < invArray->nInv; i++)
        if (strcmp(invArray->vettInv[i].nome, name) == 0)
            return i;
    printf("\nOggetto non trovato.");
    return -1;
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index) {
    inv_print(fp, &invArray->vettInv[index]);
}

