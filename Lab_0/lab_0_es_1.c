//
// Created by andrea on 24/09/19.
//
#include "stdio.h"


int main(int argc, char *argv[]) {
    int V[30];
    int i = 0, j = 0, V_lenght = 0, k = 0, lenght = 0, max = 0;
    int sub_array[15][30];

    while (i < 30) {
        V[i] = 0;
        i++;
    }

    printf("Inserire componenti intere del vettore (max 30), per interrompere inserire una lettera\n");

    while (V_lenght < 30 && scanf("%d", &V[V_lenght]) != EOF) {
        V_lenght++;
    }

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 30; j++) {
            sub_array[i][j] = 0;
        }
    }

    i = 0;

    for (j = 0; j < V_lenght; j++) {
        if (V[j] == 0) {
            i++;
            k = 0;
        } else {
            sub_array[i][k] = V[j];
            k++;
        }
    }

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 30; j++) {
            if (sub_array[i][j] != 0) {
                lenght++;
            }
        }
        if (lenght > max) {
            max = lenght;
        }
        lenght = 0;
    }

    for (i = 0; i < 15; i++) {
        for (j = 0; j < 30; j++) {
            if (sub_array[i][j] != 0) {
                lenght++;
            } else {
                break;
            }
        }
        if (lenght == max) {
            for (j = 0; j < max; j++) {
                if (sub_array[i][j] != 0) {
                    printf("%d ", sub_array[i][j]);
                }
            }
        }
        lenght = 0;
    }
}