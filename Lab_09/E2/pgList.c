//
// Created by Andrea on 16/12/2019.
//

#include "pgList.h"
#include "pg.h"

typedef struct nodoPg_t *link;

struct nodoPg_t {
    pg_t pg;
    link next;
};

struct pgList_s {
    link headPg;
    int nPg;
};

pgList_t pgList_init() {
    pgList_t p = malloc(sizeof(*p));
    p->headPg = NULL;
    p->nPg = 0;
    return p;
}

void pgList_free(pgList_t pgList){
    link x, p;
    for (x = pgList->headPg, p = NULL; x != NULL; p = x, x = x->next)
        free(p);
    free(pgList);
}

void pgList_read(FILE *fp, pgList_t pgList) {
    pg_t temp;
    int i = 0;

    while (pg_read(fp, &temp) != EOF) {
        temp.equip = equipArray_init();
        pgList_insert(pgList, temp);
        i++;
    }
    pgList->nPg = i;
}

link newNode(pg_t pg, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->pg = pg;
    x->next = next;
    return x;
}

link listInsHead(link h, pg_t pg) {
    h = newNode(pg, h);
    return h;
}

void pgList_insert(pgList_t pgList, pg_t pg) {
    pgList->headPg = listInsHead(pgList->headPg, pg);
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray) {
    link x;
    for (x = pgList->headPg; x != NULL; x = x->next)
        pg_print(fp, &x->pg, invArray);
}

pg_t *pgList_searchByCode(pgList_t pgList, char *cod) {
    link x;
    for (x = pgList->headPg; x != NULL; x = x->next)
        if (strcmp(x->pg.cod, cod) == 0)
            return &x->pg;
    return NULL;
}

void pgList_remove(pgList_t pgList, char* cod){
    link x, p; int found = 0;
    for (x = pgList->headPg, p = NULL; x != NULL && found == 0; p = x, x = x->next) {
        if (strcmp(x->pg.cod, cod) == 0) {
            found = 1;
            if (x == pgList->headPg)
                pgList->headPg = x->next;
            else
                p->next = x->next;
            free(x);
        }
    }
    if (found == 0)
        printf("\nPersonaggio non trovato.n\n");
}
