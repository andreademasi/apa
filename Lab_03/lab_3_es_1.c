//
// Created by Andrea De Masi on 20/10/19.
//

#include <stdio.h>
#include <stdlib.h>

#define MAXR 50

void leggiMatrice(int m[MAXR][MAXR], int *row, int *column);

int riconosciRegione(int m[MAXR][MAXR], int i, int j, int colonne, int righe, int *base, int *altezza);

int lookRight(int m[MAXR][MAXR], int i, int j, int colonne);

int lookDown(int m[MAXR][MAXR], int i, int j, int righe);

int main() {
    int matrix[MAXR][MAXR], righe, colonne, i, j, base, altezza;

    leggiMatrice(matrix, &righe, &colonne);

    for (i = 0; i < righe; i++) {
        for (j = 0; j < colonne; j++) {
            if (riconosciRegione(matrix, i, j, colonne, righe, &base, &altezza)) {
                printf("estr. sup. SX=<%d,%d> b=%d, h=%d\n", i, j, base, altezza);
            }
        }
    }
}

int lookRight(int m[MAXR][MAXR], int i, int j, int colonne) {
    int k, base = 1;
    for (k = 1; k < colonne - j; k++) {
        if (m[i][j + k] != 0)
            base++;
        else
            break;
    }
    return base;
}

int lookDown(int m[MAXR][MAXR], int i, int j, int righe) {
    int k, altezza = 1;
    for (k = 1; k < righe - i; k++) {
        if (m[i + k][j] != 0)
            altezza++;
        else
            break;
    }
    return altezza;
}

void leggiMatrice(int m[MAXR][MAXR], int *row, int *column) {

    FILE *fp;

    if ((fp = fopen("/home/andrea/apa/Lab_02/es1.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(99);
    }

    fscanf(fp, "%d %d", row, column);

    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *column; j++) {
            fscanf(fp, "%d ", &m[i][j]);
        }
    }
    fclose(fp);
}

int riconosciRegione(int m[MAXR][MAXR], int i, int j, int colonne, int righe, int *base, int *altezza) {
    if (m[i][j] != 0) {
        if (i != 0 && j != 0) {
            if (m[i - 1][j] == 0 && m[i][j - 1] == 0) {
                *base = lookRight(m, i, j, colonne);
                *altezza = lookDown(m, i, j, righe);
                return 1;
            } else
                return 0;
        } else if (j == 0 && i != 0) {
            if (m[i - 1][j] == 0) {
                *base = lookRight(m, i, j, colonne);
                *altezza = lookDown(m, i, j, righe);
                return 1;
            } else
                return 0;
        } else if (j != 0) {
            if (m[i][j - 1] == 0) {
                *base = lookRight(m, i, j, colonne);
                *altezza = lookDown(m, i, j, righe);
                return 1;
            } else
                return 0;
        } else {
            *base = lookRight(m, i, j, colonne);
            *altezza = lookDown(m, i, j, righe);
            return 1;
        }
    } else
        return 0;
}