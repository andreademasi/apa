//
// Created by Andrea on 16/12/2019.
//
#include "pg.h"

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    fprintf(fp, "Codice: %s\tNome: %s\tClasse: %s\t", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat, MIN_STAT);
    equipArray_print(fp, pgp->equip, invArray);
}

int pg_read(FILE *fp, pg_t *pgp) {
    pgp->equip = equipArray_init();
    return fscanf(fp, "%s %s %s %d %d %d %d %d %d", pgp->cod, pgp->nome, pgp->classe, &pgp->b_stat.hp,
                  &pgp->b_stat.mp, &pgp->b_stat.atk, &pgp->b_stat.def, &pgp->b_stat.mag, &pgp->b_stat.spr);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip, invArray);
}