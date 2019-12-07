//
// Created by Andrea De Masi on 07/12/2019.
//

#ifndef APA_INVENTORY_H
#define APA_INVENTORY_H

typedef struct {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char nome[51];
    char tipo[51];
    stat_t stat;
} Item;

typedef struct {
    int inUso;
    Item *vettEq[8];
} tabEquip_t;

typedef struct {
    Item *vettInv;
    int nInv;
    int maxInv;
} tabInv_t;

Item *searchInventory(char *nome_oggetto, tabInv_t *tabInv);

void loadInventory(tabInv_t *tabInv);

void printInv(tabInv_t *tabInv);

void printObject(Item *object);

#endif //APA_INVENTORY_H
