//
// Created by Andrea De Masi on 13/10/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void openFile(char c[20][6], int *row);

int main() {
    char string[201], sequence[20][6], word[26];
    int sequences, i = 0, j, words = 0, k = 0, n, occurrencies = 0, punct = 1;
    FILE *fp;

    openFile(sequence, &sequences);

    if ((fp = fopen("/home/andrea/apa/Lab_02/testo.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(99);
    }

    for (j = 0; j < sequences; j++) {
        printf("\nLa sequenza %s è presente in: ", sequence[j]);
        for (n = 0; sequence[j][n] != '\0'; n++) {
            sequence[j][n] = tolower(sequence[j][n]);
        }
        while (fgets(string, 200, fp) != NULL) {
            while (string[i] != '\0') {
                if (isalnum(string[i])) {
                    word[k] = tolower(string[i]);
                    k++;
                    punct = 0;
                } else {
                    if (punct == 0) {
                        if (isspace(string[i]))
                            words++;
                        else if (ispunct(string[i])) {
                            words++;
                            punct = 1;
                        } else if (iscntrl(string[i]))
                            words++;
                    }
                    word[k] = '\0';
                    if (strstr(word, sequence[j]) != NULL) {
                        printf("%s (posizione %d), ", word, words);
                        occurrencies++;
                    }
                    k = 0;
                }
                i++;
                if (occurrencies == 10)
                    break;
            }
            k = 0;
            i = 0;
        }
        words = 0;
        occurrencies = 0;
        rewind(fp);
    }
}

void openFile(char c[20][6], int *row) {

    FILE *fp;

    if ((fp = fopen("/home/andrea/apa/Lab_02/sequenze.txt", "r")) == NULL) {
        printf("Errore apertura file");
        exit(99);
    }

    fscanf(fp, "%d", row);

    for (int i = 0; i < *row; i++) {
        fscanf(fp, "%s", c[i]);
    }
    fclose(fp);
}

