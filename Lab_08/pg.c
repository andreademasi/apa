//
// Created by Andrea De Masi on 07/12/2019.
//

#include "pg.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void pushPg(tabPg_t *tabPg) {
    pg_t temp;
    printf("\nInserire dati personaggio nel formato:\n");
    printf("<codice> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>");
    scanf("%s %s %s %d %d %d %d %d %d", temp.codice, temp.nome, temp.classe, &temp.stat.hp,
          &temp.stat.mp, &temp.stat.atk, &temp.stat.def, &temp.stat.mag, &temp.stat.spr);
    temp.equip.inUso = 0;
    tabPg->headPg = listInsHead(tabPg->headPg, temp);
    printf("\nPG aggiunto. Per aggiungere l'equipaggiamento al personaggio usare la funzione di modifica dell'equip.\n");
}

link deletePg(link h) {
    link x, p;
    char codice[8];
    int found = 0;
    if (h == NULL)
        return NULL;
    printf("\nInserire codice personaggio da eliminare: ");
    scanf("%s", codice);
    for (x = h, p = NULL; x != NULL && found == 0; p = x, x = x->next) {
        if (strcmp(x->pg.codice, codice) == 0) {
            found = 1;
            if (x == h)
                h = x->next;
            else
                p->next = x->next;
            free(x);
        }
    }
    if (found == 0)
        printf("\nPersonaggio non trovato.n\n");
    return h;
}

void editInv(tabPg_t *tabPg, tabInv_t *tabInv) {
    int i, j, found = 0;
    char codice[8], nome_oggetto[51], scelta[11];
    link x;
    Item *object;

    printf("\nInserire codice personaggio da modificare: ");
    scanf("%s", codice);
    for (x = tabPg->headPg; x != NULL && found == 0; x = x->next) {
        if (strcmp(x->pg.codice, codice) == 0) {
            found = 1;
            if (x->pg.equip.inUso == 0)
                printf("Nessun oggetto equipaggiato.\n");
            else {
                printf("Inventario equipaggiato:\n");
                for (i = 0; i < x->pg.equip.inUso; i++)
                    if (x->pg.equip.vettEq[i] != NULL) {
                        printObject(x->pg.equip.vettEq[i]);
                    }
            }
        }
    }
    if (found == 0)
        printf("\nPg non trovato.\n");
    else {
        if (x == NULL) // Se è stato trovato ma x è NULL significa che il pg si trova in coda
            x = tabPg->tailPg;
        printf("\nCosa vuoi fare? (aggiungere/rimuovere): ");
        scanf("%s", scelta);
        if (strcmp(scelta, "aggiungere") == 0) {
            if (x->pg.equip.inUso == 8) {
                printf("\nInventario pieno.");
                return;
            }
            printInv(tabInv);
            printf("\nInserire nome oggetto da equipaggiare:");
            scanf("%s", nome_oggetto);
            if ((object = searchInventory(nome_oggetto, tabInv)) != NULL) {
                x->pg.equip.vettEq[x->pg.equip.inUso] = object;
                x->pg.equip.inUso++;
            } else
                printf("\nOggetto non trovato.");
            printf("Inventario equipaggiato:\n");
            for (i = 0; i < x->pg.equip.inUso; i++)
                if (x->pg.equip.vettEq[i] != NULL) {
                    printObject(x->pg.equip.vettEq[i]);
                }

        } else if (strcmp(scelta, "rimuovere") == 0) {
            if (x->pg.equip.inUso == 0)
                printf("Nessun oggetto equipaggiato.\n");
            else {
                found = 0;
                printf("Inventario equipaggiato:\n");
                for (i = 0; i < x->pg.equip.inUso; i++)
                    if (x->pg.equip.vettEq[i] != NULL) {
                        printObject(x->pg.equip.vettEq[i]);
                    }
                printf("\nInserire nome oggetto da rimuovere:");
                scanf("%s", nome_oggetto);
                for (i = 0; i < x->pg.equip.inUso && found == 0; i++) {
                    if (strcmp(nome_oggetto, x->pg.equip.vettEq[i]->nome) == 0) {
                        for (j = i; j < x->pg.equip.inUso - 1; j++)
                            x->pg.equip.vettEq[j] = x->pg.equip.vettEq[j + 1];
                        x->pg.equip.inUso--;
                        found = 1;
                    }
                }
                if (!found)
                    printf("Oggetto non trovato");
            }
        } else
            printf("\nScelta errata.");
    }
}

void getStats(tabPg_t *tabPg) {
    int found = 0, i, stats[6];
    char codice[8];
    link x;

    printf("\nInserire codice personaggio di cui calcolare le statistiche: ");
    scanf("%s", codice);
    for (x = tabPg->headPg; x != NULL && found == 0; x = x->next) {
        if (strcmp(x->pg.codice, codice) == 0) {
            found = 1;
            if (x->pg.equip.inUso == 0) {
                printf("Nessun oggetto equipaggiato.\n");
                break;
            } else {
                stats[0] = x->pg.stat.hp;
                stats[1] = x->pg.stat.mp;
                stats[2] = x->pg.stat.atk;
                stats[3] = x->pg.stat.def;
                stats[4] = x->pg.stat.mag;
                stats[5] = x->pg.stat.spr;
                for (i = 0; i < x->pg.equip.inUso; i++) {
                    stats[0] += x->pg.equip.vettEq[i]->stat.hp;
                    stats[1] += x->pg.equip.vettEq[i]->stat.mp;
                    stats[2] += x->pg.equip.vettEq[i]->stat.atk;
                    stats[3] += x->pg.equip.vettEq[i]->stat.def;
                    stats[4] += x->pg.equip.vettEq[i]->stat.mag;
                    stats[5] += x->pg.equip.vettEq[i]->stat.spr;
                }
            }
        }
    }
    if (found == 0)
        printf("\nPg non trovato.\n");
    else {
        for (i = 0; i < 6; i++) {
            if (stats[i] < 1)
                stats[i] = 1;
        }
        printf("HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n", stats[0], stats[1], stats[2], stats[3], stats[4],
               stats[5]);
    }
}

void loadPg(tabPg_t *tabPg) {
    FILE *fp;
    int i = 0;
    pg_t temp;
    fp = fopen("C:\\Users\\andre\\apa\\Lab_08\\pg.txt", "r");

    tabPg->headPg = NULL;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", temp.codice, temp.nome, temp.classe, &temp.stat.hp,
                  &temp.stat.mp, &temp.stat.atk, &temp.stat.def, &temp.stat.mag, &temp.stat.spr) !=
           EOF) {
        temp.equip.inUso = 0;
        tabPg->headPg = listInsHead(tabPg->headPg, temp);
        i++;
    }
    tabPg->nPg = i;
    for (tabPg->tailPg = tabPg->headPg; tabPg->tailPg->next != NULL; tabPg->tailPg = tabPg->tailPg->next);
    //Raggiungo la coda della lista e la assegno a tailPg
    fclose(fp);
}
