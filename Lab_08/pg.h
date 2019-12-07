//
// Created by Andrea De Masi on 07/12/2019.
//

#ifndef APA_PG_H
#define APA_PG_H

#include "inventory.h"

typedef struct nodoPg_t *link;

typedef struct {
    char codice[8];
    char nome[50];
    char classe[50];
    tabEquip_t equip;
    stat_t stat;
} pg_t;

struct nodoPg_t {
    pg_t pg;
    link next;
};

typedef struct {
    link headPg;
    link tailPg;
    int nPg;
} tabPg_t;

void pushPg(tabPg_t *tabPg);

link deletePg(link h);

void editInv(tabPg_t *tabPg, tabInv_t *tabInv);

void getStats(tabPg_t *tabPg);

void loadPg(tabPg_t *tabPg);

#endif //APA_PG_H
