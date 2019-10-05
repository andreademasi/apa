//
// Created by andrea on 02/10/19.
//

#include <stdio.h>


int main() {
    int campionato[20][20], giornata, i = 0, j = 0, righe = 0, colonne = 0, capolista = 0;
    char c;
    FILE *f;

    if ((f = fopen("/home/andrea/apa/Lab_01/campionato.txt", "r")) == NULL) {
        printf("Errore file");
        return 1;
    }

    while (fscanf(f, "%d%c", &giornata, &c) != EOF) {
        if (c != ' ') {
            campionato[i][j] = giornata + campionato[i][j - 1];
            i++;
            j = 0;
        } else if (j == 0) {
            campionato[i][j] = giornata;
            j++;
        } else {
            campionato[i][j] = giornata + campionato[i][j - 1];
            j++;
        }
    }

    fclose(f);

    colonne = j;
    righe = i + 1;

    for (j = 0; j < colonne; j++) {
        for (i = 0; i < righe; i++) {
            if (campionato[i][j] > campionato[capolista][j]) {
                capolista = i;
            }
        }
        printf("La capolista della giornata %d è la squadra numero %d\n", j + 1, capolista + 1);
        capolista = 0;
    }

    return 0;
}
