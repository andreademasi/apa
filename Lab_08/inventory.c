//
// Created by Andrea De Masi on 07/12/2019.
//

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadInventory(tabInv_t *tabInv) {
    FILE *fp;
    int i = 0;
    fp = fopen("C:\\Users\\andre\\apa\\Lab_08\\inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);

    tabInv->vettInv = malloc(tabInv->nInv * sizeof(Item));

    while (fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo,
                  &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
                  &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr) != EOF)
        i++;
    fclose(fp);
}

Item *searchInventory(char *nome_oggetto, tabInv_t *tabInv) {
    int i;
    for (i = 0; i < tabInv->nInv; i++) {
        if (strcmp(nome_oggetto, tabInv->vettInv[i].nome) == 0) {
            return &tabInv->vettInv[i];
        }
    }
    return NULL;
}

void printInv(tabInv_t *tabInv) {
    int i;
    printf("\nInventario disponibile:\n");
    for (i = 0; i < tabInv->nInv; i++) {
        printf("Nome: %s Tipo: %s HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n", tabInv->vettInv[i].nome,
               tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp, tabInv->vettInv[i].stat.mp,
               tabInv->vettInv[i].stat.atk, tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag,
               tabInv->vettInv[i].stat.spr);
    }
}

void printObject(Item *object) {
    printf("Nome: %s Tipo: %s HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n",
           object->nome, object->tipo, object->stat.hp, object->stat.mp, object->stat.atk, object->stat.def,
           object->stat.mag, object->stat.spr);
}