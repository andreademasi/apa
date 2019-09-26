//
// Created by Andrea De Masi on 26/09/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    FILE *f;
    char file_name[40]; //dovrebbe essere 20
    int row_number, column_number, matrix[20][20], big_matrix[20][20], i, j, k, l, dim, sum = 0, previous_sum = 0;

    printf("Inserire percorso file: ");
    scanf("%s", file_name);

    if (((f = fopen(file_name, "r")) == NULL)) {
        printf("Opening file ERROR");
        exit(98);
    } else {
        fscanf(f, "%d %d", &row_number, &column_number);
        for (i = 0; i < row_number; i++) {
            for (j = 0; j < column_number; j++) {
                fscanf(f, "%d", &matrix[i][j]);
            }
        }
        while (1) {
            printf("\nInserire un valore compreso tra 1 e il minimo tra nr e nc: ");
            scanf("%d", &dim);
            if (dim <= 1 || dim > fmin(row_number, column_number))
                break;
            for (l = 0; l < row_number - dim + 1; l++) {
                for (k = 0; k < column_number - dim + 1; k++) {
                    for (i = 0; i < dim; i++) {
                        for (j = 0; j < dim; j++) {
                            printf("%d ", matrix[i + l][j + k]);
                            sum += matrix[i + l][j + k];
                            big_matrix[i][j] = matrix[i + l][j + k];
                        }
                        printf("\n");
                    }
                    if (sum > previous_sum) {
                        previous_sum = sum;
                        for (i = 0; i < dim; i++) {
                            for (j = 0; j < dim; j++) {
                                big_matrix[i][j] = matrix[i + l][j + k];
                            }
                        }
                    }
                    sum = 0;
                    printf("\n*COLONNA SUCCESSIVA*\n");
                }
                printf("\n*RIGA SUCCESSIVA*\n");
            }
            printf("Sottomatrice quadrata la cui somma di elementi è massima:\n");
            for (i = 0; i < dim; i++) {
                for (j = 0; j < dim; j++) {
                    printf("%d ", big_matrix[i][j]);
                }
                printf("\n");
            }
        }
    }
}


