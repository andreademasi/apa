//
// Created by Andrea De Masi on 27/11/19.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct nodoPg_t *link;

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

typedef enum {
    r_aggiungi, r_elimina, r_modifica, r_calcola, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comando_e cmd);

void loadPg(tabPg_t *tabPg);

void loadInventory(tabInv_t *tabInv);

link listInsHead(link h, pg_t pg);

link newNode(pg_t pg, link next);

void pushPg(tabPg_t *tabPg);

link deletePg(link h);

void editInv(tabPg_t *tabPg, tabInv_t *tabInv);

void printInv(tabInv_t *tabInv);

void getStats(tabPg_t *tabPg);

int main() {

    tabPg_t tabPg;
    tabInv_t tabInv;

    loadPg(&tabPg);
    loadInventory(&tabInv);
    selezionaDati(&tabPg, &tabInv, leggiComando());
}

void loadPg(tabPg_t *tabPg) {
    FILE *fp;
    int i = 0;
    pg_t temp;
    fp = fopen("/home/andrea/apa/Lab_07/pg.txt", "r");

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

void loadInventory(tabInv_t *tabInv) {
    FILE *fp;
    int i = 0;
    fp = fopen("/home/andrea/apa/Lab_07/inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);

    tabInv->vettInv = malloc(tabInv->nInv * sizeof(Item));

    while (fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome, tabInv->vettInv[i].tipo,
                  &tabInv->vettInv[i].stat.hp, &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
                  &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag, &tabInv->vettInv[i].stat.spr) != EOF)
        i++;
    fclose(fp);
}

link listInsHead(link h, pg_t pg) {
    h = newNode(pg, h);
    return h;
}

link newNode(pg_t pg, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    x->pg = pg;
    x->next = next;
    return x;
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"aggiungi", "elimina", "modifica_equip", "calcola", "fine"};
    int i;
    printf("Inserire comando (aggiungi/elimina/modifica_equip/calcola/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_aggiungi;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comando_e cmd) {
    int continua = 1;
    while (continua) {
        switch (cmd) {
            case r_aggiungi:
                pushPg(tabPg);
                cmd = leggiComando();
                break;
            case r_elimina:
                tabPg->headPg = deletePg(tabPg->headPg);
                cmd = leggiComando();
                break;
            case r_modifica:
                printf("\nAggiungi o rimuovi un oggetto dall'equipaggiamento di un personaggio\n");
                editInv(tabPg, tabInv);
                cmd = leggiComando();
                break;
            case r_calcola:
                getStats(tabPg);
                cmd = leggiComando();
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default:
                printf("comando errato\n");
                cmd = leggiComando();
                break;
        }
    }
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
                        printf("Nome: %s Tipo: %s HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n",
                               x->pg.equip.vettEq[i]->nome, x->pg.equip.vettEq[i]->tipo, x->pg.equip.vettEq[i]->stat.hp,
                               x->pg.equip.vettEq[i]->stat.mp, x->pg.equip.vettEq[i]->stat.atk,
                               x->pg.equip.vettEq[i]->stat.def,
                               x->pg.equip.vettEq[i]->stat.mag, x->pg.equip.vettEq[i]->stat.spr);
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
            found = 0;
            for (i = 0; i < tabInv->nInv && found == 0; i++) {
                if (strcmp(nome_oggetto, tabInv->vettInv[i].nome) == 0) {
                    found = 1;
                    x->pg.equip.vettEq[x->pg.equip.inUso] = &tabInv->vettInv[i];
                    x->pg.equip.inUso++;
                }
            }
            if (!found)
                printf("\nOggetto non trovato.");
            printf("Inventario equipaggiato:\n");
            for (i = 0; i < x->pg.equip.inUso; i++)
                if (x->pg.equip.vettEq[i] != NULL) {
                    printf("Nome: %s Tipo: %s HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n",
                           x->pg.equip.vettEq[i]->nome,
                           x->pg.equip.vettEq[i]->tipo, x->pg.equip.vettEq[i]->stat.hp, x->pg.equip.vettEq[i]->stat.mp,
                           x->pg.equip.vettEq[i]->stat.atk, x->pg.equip.vettEq[i]->stat.def,
                           x->pg.equip.vettEq[i]->stat.mag,
                           x->pg.equip.vettEq[i]->stat.spr);
                }

        } else if (strcmp(scelta, "rimuovere") == 0) {
            if (x->pg.equip.inUso == 0)
                printf("Nessun oggetto equipaggiato.\n");
            else {
                found = 0;
                printf("Inventario equipaggiato:\n");
                for (i = 0; i < x->pg.equip.inUso; i++)
                    if (x->pg.equip.vettEq[i] != NULL) {
                        printf("Nome: %s Tipo: %s HP: %d MP: %d ATK: %d DEF: %d MAG: %d SPR: %d\n",
                               x->pg.equip.vettEq[i]->nome,
                               x->pg.equip.vettEq[i]->tipo, x->pg.equip.vettEq[i]->stat.hp,
                               x->pg.equip.vettEq[i]->stat.mp,
                               x->pg.equip.vettEq[i]->stat.atk, x->pg.equip.vettEq[i]->stat.def,
                               x->pg.equip.vettEq[i]->stat.mag,
                               x->pg.equip.vettEq[i]->stat.spr);
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