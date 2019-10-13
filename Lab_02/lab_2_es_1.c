//
// Created by Andrea De Masi on 12/10/19.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

void openFile(int m[MAX][MAX], int *row, int *column);

typedef struct {
    int max_sup_i;
    int max_sup_j;
    int base;
    int altezza;
    int area;
} MaxRegioni;

void setRegione(int index, MaxRegioni m[], int i, int j, int base, int altezza, int area);

int lookRight(int m[MAX][MAX], int i, int j, int colonne);

int lookDown(int m[MAX][MAX], int i, int j, int righe);

int main() {
    int matrix[MAX][MAX], righe, colonne, i, j, max_base = 0, max_altezza = 0,
            max_area = 0, base, altezza, area;

    MaxRegioni maxregioni[3]; //0 = max base, 1 = max altezza, 2 = max area

    openFile(matrix, &righe, &colonne);

    for (i = 0; i < righe; i++) {
        for (j = 0; j < colonne; j++) {
            if (matrix[i][j] != 0) {
                base = lookRight(matrix, i, j, colonne);
                altezza = lookDown(matrix, i, j, righe);
                area = base * altezza;
                if (base > max_base) {
                    max_base = base;
                    setRegione(0, maxregioni, i, j, base, altezza, area);
                }
                if (altezza > max_altezza) {
                    max_altezza = altezza;
                    setRegione(1, maxregioni, i, j, base, altezza, area);
                }
                if (area > max_area) {
                    max_area = area;
                    setRegione(2, maxregioni, i, j, base, altezza, area);
                }
            }
        }
    }
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", maxregioni[0].max_sup_i, maxregioni[0].max_sup_j,
           maxregioni[0].base, maxregioni[0].altezza, maxregioni[0].area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", maxregioni[2].max_sup_i, maxregioni[2].max_sup_j,
           maxregioni[2].base, maxregioni[2].altezza, maxregioni[2].area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", maxregioni[1].max_sup_i, maxregioni[1].max_sup_j,
           maxregioni[1].base, maxregioni[1].altezza, maxregioni[1].area);
}

int lookRight(int m[MAX][MAX], int i, int j, int colonne) {
    int k, base = 1;
    for (k = 1; k < colonne - j; k++) {
        if (m[i][j + k] != 0)
            base++;
        else
            break;
    }
    return base;
}

int lookDown(int m[MAX][MAX], int i, int j, int righe) {
    int k, altezza = 1;
    for (k = 1; k < righe - i; k++) {
        if (m[i + k][j] != 0)
            altezza++;
        else
            break;
    }
    return altezza;
}

void setRegione(int index, MaxRegioni m[], int i, int j, int base, int altezza, int area) {
    m[index].max_sup_i = i;
    m[index].max_sup_j = j;
    m[index].base = base;
    m[index].altezza = altezza;
    m[index].area = area;
}

void openFile(int m[MAX][MAX], int *row, int *column) {

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
