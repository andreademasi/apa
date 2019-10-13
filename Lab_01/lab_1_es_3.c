//
// Created by andrea on 06/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void openFile(int m[30][30], int *row, int *column);

void ruota(int m[30][30], int righe, int colonne, int indice, char direzione[9], int posizioni);

int main() {

    int matrix[30][30], righe, colonne, indice, posizioni;
    char selettore[8], direzione[9];

    openFile(matrix, &righe, &colonne);
    printf("\nFormato: <selettore> <indice> <direzione> <posizioni>\nInserire comando: ");
    while (1) {
        scanf("%s %d %s %d", selettore, &indice, direzione, &posizioni);
        if (strcmp(selettore, "fine") == 0)
            break;
        ruota(matrix, righe, colonne, indice, direzione, posizioni);
        //stampa matrice ruotata
        printf("\n");
        for (int i = 0; i < righe; i++) {
            for (int j = 0; j < colonne; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    }
}

void openFile(int m[30][30], int *row, int *column) {

    char nome_file[50]; //dovrebbero essere 20 in realtà ma ne servono di più perchè inserisco l'indirizzo del file
    FILE *fp;

    printf("Inserire nome file: ");
    scanf("%s", nome_file);

    if ((fp = fopen(nome_file, "r")) == NULL) {
        printf("Errore apertura file");
        exit(99);
    }

    fscanf(fp, "%d %d", row, column);

    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *column; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
}

void ruota(int m[30][30], int righe, int colonne, int indice, char direzione[9], int posizioni) {

    int i, j, temp;
    indice--;

    if (strcmp(direzione, "sinistra") == 0) { //sinistra
        for (i = 0; i < posizioni; i++) {
            temp = m[indice][0];
            for (j = 0; j < colonne - 1; j++) {
                m[indice][j] = m[indice][j + 1];
            }
            m[indice][j] = temp;
        }
    } else if (strcmp(direzione, "destra") == 0) { //destra
        for (i = 0; i < posizioni; i++) {
            temp = m[indice][colonne - 1];
            for (j = colonne - 1; j > 0; j--) {
                m[indice][j] = m[indice][j - 1];
            }
            m[indice][0] = temp;
        }
    } else if (strcmp(direzione, "su") == 0) { //su
        for (i = 0; i < posizioni; i++) {
            temp = m[0][indice];
            for (j = 0; j < righe - 1; j++) {
                m[j][indice] = m[j + 1][indice];
            }
            m[j][indice] = temp;
        }
    } else if (strcmp(direzione, "giu") == 0) { //giu
        for (i = 0; i < posizioni; i++) {
            temp = m[righe - 1][indice];
            for (j = righe - 1; j > 0; j--) {
                m[j][indice] = m[j - 1][indice];
            }
            m[0][indice] = temp;
        }
    }
}
