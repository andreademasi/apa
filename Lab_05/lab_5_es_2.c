//
// Created by Andrea De Masi on 13/11/19.
//

#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int *nr, int *nc);

void separa(int **mat, int nr, int nc, int *blacks, int *whites);

int main() {
    int **matrix, nr, nc, i, *blacks, *whites;

    matrix = malloc2dR(&nr, &nc);

    blacks = malloc((nr * nc / 2 + 1) * sizeof(int));
    whites = malloc(nr * nc / 2 * sizeof(int));

    separa(matrix, nr, nc, blacks, whites);

    for (i = 0; i < (nr * nc / 2 + 1); i++)
        printf("%d ", blacks[i]);
    printf("\n");
    for (i = 0; i < nr * nc / 2; i++)
        printf("%d ", whites[i]);

    free(blacks);
    free(whites);
}

int **malloc2dR(int *nr, int *nc) {
    FILE *fp;
    int **matrix, i, j;

    fp = fopen("/home/andrea/apa/Lab_05/mat.txt", "r");

    fscanf(fp, "%d %d", nr, nc);

    matrix = malloc(*nr * sizeof(int *));

    for (i = 0; i < *nr; i++)
        matrix[i] = malloc(*nc * sizeof(int));

    for (i = 0; i < *nr; i++) {
        for (j = 0; j < *nc; j++)
            fscanf(fp, "%d", &matrix[i][j]);
    }

    return matrix;
}

void separa(int **mat, int nr, int nc, int *blacks, int *whites) {
    int i, j, k = 0, m = 0, n = 0;

    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            if (k % 2 == 0) {
                blacks[m] = mat[i][j];
                m++;
            } else {
                whites[n] = mat[i][j];
                n++;
            }
            k++;
        }
    }
}