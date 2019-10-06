//
// Created by Andrea De Masi on 25/09/19.
//

#include <stdio.h>
#include <stdlib.h>

#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

int main() {
    int array_length, array[maxN], i = 0, P, dir;

    printf("Inserire la lunghezza del vettore (massimo %d): ", maxN);

    scanf("%d", &array_length);
    if (array_length > maxN) {
        printf("\nLunghezza vettore superata");
        exit(98);
    }

    printf("\nInserire componenti del vettore: ");

    while (i < array_length) {
        scanf("%d", &array[i]);
        i++;
    }

    while (1) {
        printf("Inserire numero di posizioni da ruotare (0 per interrompere): ");
        scanf("%d", &P);
        if (P == 0) {
            exit(0);
        }
        printf("Inserire direzione (-1 per ruotare a destra o 1 per ruotare a sinistra): ");
        scanf("%d", &dir);
        ruota(array, array_length, P, dir);
    };
}

void ruota(int v[maxN], int N, int P, int dir) {
    int i, j, temp;
    if (dir == 1) {
        for (i = 0; i < P; i++) {
            temp = v[0];
            for (j = 0; j < N - 1; j++) {
                v[j] = v[j + 1];
            }
            v[j] = temp;
        }
    } else if (dir == -1) {
        for (i = 0; i < P; i++) {
            temp = v[N - 1];
            for (j = N - 1; j > 0; j--) {
                v[j] = v[j - 1];
            }
            v[0] = temp;
        }
    }

    for (i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}