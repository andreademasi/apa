//
// Created by Andrea De Masi on 04/11/19.
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
    r_stampa, r_date, r_partenza, r_capolinea, r_codice_tratta, r_ricerca, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(Corsa c[MAX], int dim, comando_e cmd);

void printLog(Corsa c[MAX], int dim, int video);

void openFile(Corsa c[MAX], int *row);

int ITEMlt(Corsa *A, Corsa *B, comando_e cmd);

int BinSearch(Corsa v[], int l, int r, char k[20]);

int LinearSearch(Corsa v[], int l, int r, char k[20]);

void InsertionSort(Corsa *A[], int N, comando_e cmd);

void printRef(Corsa **sorting, int dim);

int main() {

    int righe;
    Corsa corse[MAX];

    openFile(corse, &righe);
    selezionaDati(corse, righe, leggiComando());
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"stampa", "date", "partenza", "capolinea", "cod_tratta", "ricerca", "fine"};
    int i;
    printf("Inserire comando (stampa/date/partenza/capolinea/cod_tratta/ricerca/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_stampa;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void selezionaDati(Corsa c[MAX], int dim, comando_e cmd) {
    int continua = 1, video = 0, sorted = 0, k, i;
    char key[20];
    Corsa *date[dim], *partenza[dim], *capolinea[dim], *codice_tratta[dim];
    for (i = 0; i < dim; i++) {
        partenza[i] = capolinea[i] = codice_tratta[i] = date[i] = &c[i];
    }
    while (continua) {
        switch (cmd) {
            case r_stampa:
                printf("Inserire 1 per stampare a video, 0 per stampare su file: ");
                scanf("%d", &video);
                printLog(c, dim, video);
                cmd = leggiComando();
                break;
            case r_date:
                InsertionSort(date, dim, cmd);
                printRef(date, dim);
                cmd = leggiComando();
                break;
            case r_partenza:
                InsertionSort(partenza, dim, cmd);
                sorted = 1;
                printRef(partenza, dim);
                cmd = leggiComando();
                break;
            case r_capolinea:
                InsertionSort(capolinea, dim, cmd);
                sorted = 0;
                printRef(capolinea, dim);
                cmd = leggiComando();
                break;
            case r_codice_tratta:
                InsertionSort(codice_tratta, dim, cmd);
                sorted = 0;
                printRef(codice_tratta, dim);
                cmd = leggiComando();
                break;
            case r_ricerca:
                printf("Inserire la chiave: ");
                scanf("%s", key);
                if (sorted)
                    k = BinSearch(c, 0, dim - 1, key);
                else
                    k = LinearSearch(c, 0, dim - 1, key);
                if (k != -1)
                    printf("%s %s %s %s %d %d %d\n", c[k].codice_tratta, c[k].partenza, c[k].destinazione, c[k].data,
                           c[k].ora_partenza, c[k].ora_arrivo, c[k].ritardo);
                else
                    printf("Stazione di partenza non trovata.\n");
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

void InsertionSort(Corsa *A[], int N, comando_e cmd) {
    int i, j, l = 0, r = N - 1;
    Corsa *x;
    for (i = l + 1; i <= r; i++) {
        x = A[i];
        j = i - 1;
        while (j >= l && ITEMlt(x, A[j], cmd)) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = x;
    }
}

int BinSearch(Corsa v[], int l, int r, char k[20]) {
    int m;
    while (l <= r) {
        m = (l + r) / 2;
        if (strcmp(v[m].partenza, k) == 0)
            return (m);
        if (strcmp(v[m].partenza, k) < 0)
            l = m + 1;
        else
            r = m - 1;
    }
    return (-1);
}

int LinearSearch(Corsa v[], int l, int r, char k[20]) {
    int i = l;
    while (i <= r) {
        if (strcmp(v[i].partenza, k) == 0)
            return i;
        else
            i++;
    }
    return -1;
}

int ITEMlt(Corsa *A, Corsa *B, comando_e cmd) {
    switch (cmd) {
        case r_date:
            if (strcmp(A->data, B->data) < 0)
                return 1;
            else if (strcmp(A->data, B->data) == 0) {
                if (A->ora_partenza < B->ora_partenza)
                    return 1;
                return 0;
            }
            return 0;
        case r_partenza:
            if (strcmp(A->partenza, B->partenza) < 0)
                return 1;
            return 0;
        case r_capolinea:
            if (strcmp(A->destinazione, B->destinazione) < 0)
                return 1;
            return 0;
        case r_codice_tratta:
            if (strcmp(A->codice_tratta, B->codice_tratta) < 0)
                return 1;
            return 0;
        default:
            return -1;
    }
}

void openFile(Corsa c[MAX], int *row) {

    FILE *fp;

    if ((fp = fopen("/home/andrea/apa/Lab_04/corse.txt", "r")) == NULL) {
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

void printLog(Corsa c[MAX], int dim, int video) {
    int i;
    FILE *fp;

    if (video) {
        for (i = 0; i < dim; i++)
            printf("%s %s %s %s %d %d %d\n", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
                   c[i].ora_partenza, c[i].ora_arrivo, c[i].ritardo);
    } else {
        fp = fopen("log.txt", "w+");
        for (i = 0; i < dim; i++)
            fprintf(fp, "%s %s %s %s %d %d %d\n", c[i].codice_tratta, c[i].partenza, c[i].destinazione, c[i].data,
                    c[i].ora_partenza, c[i].ora_arrivo, c[i].ritardo);
        fclose(fp);
    }
}

void printRef(Corsa **sorting, int dim) {
    int i;
    for (i = 0; i < dim; i++)
        printf("%s %s %s %s %d %d %d\n", sorting[i]->codice_tratta, sorting[i]->partenza, sorting[i]->destinazione,
               sorting[i]->data, sorting[i]->ora_partenza, sorting[i]->ora_arrivo, sorting[i]->ritardo);
}
