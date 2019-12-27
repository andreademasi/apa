//
// Created by Andrea on 16/12/2019.
//

#include "equipArray.h"

struct equipArray_s {
    int equip[EQUIP_SLOT];
    int inUso;
};

equipArray_t equipArray_init() {
    int i;
    equipArray_t e = malloc(sizeof(*e));
    for (i = 0; i < EQUIP_SLOT; i++)
        e->equip[i] = -1;
    e->inUso = 0;
    return e;
}

void equipArray_free(equipArray_t equipArray) {
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray) {
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    int i;
    if (equipArray->inUso == 0) {
        printf("\nNessun oggetto equipaggiato.");
        return;
    }
    printf("\nOggetti equipaggiati:");
    for (i = 0; i < equipArray->inUso; i++)
        invArray_printByIndex(fp, invArray, equipArray->equip[i]);
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray) {
    int index;
    char name[LEN];
    invArray_print(stdout, invArray);
    equipArray_print(stdout, equipArray, invArray);
    printf("Inserire nome dell'oggetto dell'inventario da equipaggiare: ");
    scanf("%s", name);
    index = invArray_searchByName(invArray, name);
    if (index != -1) {
        equipArray->equip[equipArray->inUso] = index;
        equipArray->inUso++;
    }
}