//
// Created by Andrea on 16/12/2019.
//

#include "inv.h"

void inv_print(FILE *fp, inv_t *invp) {
    printf("Nome: %s Tipo: %s ", invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, MIN_STAT);
    printf("\n");
}

void stat_print(FILE *fp, stat_t *statp, int soglia) {
    int stats[6], i;
    stats[0] = statp->hp;
    stats[1] = statp->mp;
    stats[2] = statp->atk;
    stats[3] = statp->def;
    stats[4] = statp->mag;
    stats[5] = statp->spr;

    for (i = 0; i < 6; i++)
        if(stats[i] < soglia)
            stats[i] = 1;

    fprintf(fp,"HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n", stats[0], stats[1], stats[2], stats[3], stats[4],
           stats[5]);
}