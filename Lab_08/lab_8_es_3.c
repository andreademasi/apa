//
// Created by Andrea De Masi on 07/12/19.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "inventory.h"
#include "pg.h"

typedef enum {
    r_aggiungi, r_elimina, r_modifica, r_calcola, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comando_e cmd);

int main() {

    tabPg_t tabPg;
    tabInv_t tabInv;

    loadPg(&tabPg);
    loadInventory(&tabInv);
    selezionaDati(&tabPg, &tabInv, leggiComando());
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