//
// Created by Andrea De Masi on 12/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char codice_tratta[31];
    char partenza[31];
    char destinazione[31];
    char data[11];
    int ora_partenza;
    int ora_arrivo;
    int ritardo;
} Corsa;

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(Corsa c[MAX], int dim, comando_e cmd);

int scanDate(int anno1, int anno2, int mese1, int mese2, int giorno1, int giorno2, int anno_corsa,
             int mese_corsa, int giorno_corsa);

void CorseInDate(Corsa *c, int dim, char *data1, char *data2);

void CorseInDateInRitardo(Corsa *c, int dim, char *data1, char *data2);

void PartenzaOrCapolinea(Corsa c[MAX], int dim, char fermata[21], int PoC);

void RitardoTot(Corsa c[MAX], int dim, char codice_tratta[21]);

void openFile(Corsa c[MAX], int *row);

int main() {

    int righe;
    Corsa corse[MAX];

    openFile(corse, &righe);
    selezionaDati(corse, righe, leggiComando());
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    int i;
    printf("Inserire comando (date/partenza/capolinea/ritardo_tot/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_date;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void selezionaDati(Corsa c[MAX], int dim, comando_e cmd) {
    char codice[21], fermata[21], data1[21], data2[21];
    int continua = 1;
    while (continua) {
        switch (cmd) {
            case r_date:
                printf("Inserire intervallo date (<data1> <data2>): ");
                scanf("%s %s", data1, data2);
                CorseInDate(c, dim, data1, data2);
                cmd = leggiComando();
                break;
            case r_partenza:
                printf("Inserire fermata: ");
                scanf("%s", fermata);
                PartenzaOrCapolinea(c, dim, fermata, 1);
                cmd = leggiComando();
                break;
            case r_capolinea:
                printf("Inserire fermata: ");
                scanf("%s", fermata);
                PartenzaOrCapolinea(c, dim, fermata, 0);
                cmd = leggiComando();
                break;
            case r_ritardo:
                printf("Inserire intervallo date (<data1> <data2>): ");
                scanf("%s %s", data1, data2);
                CorseInDateInRitardo(c, dim, data1, data2);
                cmd = leggiComando();
                break;
            case r_ritardo_tot:
                printf("Inserire codice tratta: ");
                scanf("%s", codice);
                RitardoTot(c, dim, codice);
                cmd = leggiComando();
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default:
                printf("comando errato\n");
        }
    }
}

int scanDate(int anno1, int anno2, int mese1, int mese2, int giorno1, int giorno2, int anno_corsa,
             int mese_corsa, int giorno_corsa) {

    if (anno_corsa <= anno2 && anno_corsa >= anno1) {
        if (mese_corsa <= mese2 && mese_corsa >= mese1) {
            if (giorno_corsa <= giorno2 && giorno_corsa >= giorno1) {
                return 1;
            } else
                return 0;
        } else
            return 0;
    } else
        return 0;
}

void CorseInDate(Corsa *c, int dim, char *data1, char *data2) {
    int i, giorno_corsa, mese_corsa, anno_corsa, giorno1, mese1, anno1, giorno2, mese2, anno2;

    sscanf(data1, "%d/%d/%d", &giorno1, &mese1, &anno1);
    sscanf(data2, "%d/%d/%d", &giorno2, &mese2, &anno2);

    for (i = 0; i < dim; i++) {
        sscanf(c[i].data, "%d/%d/%d", &giorno_corsa, &mese_corsa, &anno_corsa);
        if (scanDate(anno1, anno2, mese1, mese2, giorno1, giorno2, anno_corsa, mese_corsa, giorno_corsa)) {
            printf("%s %s %s %s %d %d %d\n", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
                   c[i].ora_partenza, c[i].ora_arrivo, c[i].ritardo);
        }
    }
}

void CorseInDateInRitardo(Corsa *c, int dim, char *data1, char *data2) {
    int i, giorno_corsa, mese_corsa, anno_corsa, giorno1, mese1, anno1, giorno2, mese2, anno2;

    sscanf(data1, "%d/%d/%d", &giorno1, &mese1, &anno1);
    sscanf(data2, "%d/%d/%d", &giorno2, &mese2, &anno2);

    for (i = 0; i < dim; i++) {
        sscanf(c[i].data, "%d/%d/%d", &giorno_corsa, &mese_corsa, &anno_corsa);
        if (scanDate(anno1, anno2, mese1, mese2, giorno1, giorno2, anno_corsa, mese_corsa, giorno_corsa)) {
            if (c[i].ritardo != 0)
                printf("%s %s %s %s %d %d %d\n", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
                       c[i].ora_partenza, c[i].ora_arrivo, c[i].ritardo);
        }
    }
}

void PartenzaOrCapolinea(Corsa c[MAX], int dim, char fermata[21], int PoC) {
    int i;

    for (i = 0; i < dim; i++) {
        if (PoC) {
            if (strcmp(c[i].partenza, fermata) == 0)
                printf("%s %s %s %s %d %d %d\n", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
                       c[i].ora_partenza, c[i].ora_arrivo, c[i].ritardo);
        } else {
            if (strcmp(c[i].destinazione, fermata) == 0)
                printf("%s %s %s %s %d %d %d\n", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
                       c[i].ora_partenza, c[i].ora_arrivo, c[i].ritardo);
        }
    }
}

void RitardoTot(Corsa c[MAX], int dim, char codice_tratta[21]) {
    int i, ritardo = 0;

    for (i = 0; i < dim; i++) {
        if (strcmp(codice_tratta, c[i].codice_tratta) == 0)
            ritardo += c[i].ritardo;
    }

    printf("Il ritardo totale della tratta %s è: %d\n", codice_tratta, ritardo);
}

void openFile(Corsa c[MAX], int *row) {

    FILE *fp;

    if ((fp = fopen("/home/andrea/apa/Lab_02/corse.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(99);
    }

    fscanf(fp, "%d", row);

    for (int i = 0; i < *row; i++) {
        fscanf(fp, "%s %s %s %s %d %d %d", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
               &c[i].ora_partenza, &c[i].ora_arrivo, &c[i].ritardo);
    }
    fclose(fp);
}