//
// Created by Andrea De Masi on 25/09/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int conta(char S[20], int n);

int main() {
    FILE *f;
    char file_name[20], string[20];
    int substring_length, total_words = 0, count = 0;

    printf("Inserire percorso file: ");
    scanf("%s", file_name);
    printf("\nInserire lunghezza sottostringhe: ");
    scanf("%d", &substring_length);

    if (((f = fopen(file_name, "r")) == NULL)) {
        printf("Opening file ERROR");
        exit(98);
    } else {
        fscanf(f, "%d", &total_words);
        for (int i = 0; i < total_words; i++) {
            fscanf(f, "%s", string);
            count += conta(string, substring_length);
        }
        printf("Le sottostringhe con 2 vocali sono: %d", count);
    }
}

int conta(char S[20], int n) {
    int i, j, len, vowels = 0, words = 0;
    len = strlen(S);
    for (i = 0; i != len - n - 1; i++) {
        for (j = 0; j < n; j++) {
            if (tolower(S[j + i]) == 'a' || tolower(S[j + i]) == 'e' || tolower(S[j + i]) == 'i' ||
                tolower(S[j + i]) == 'o' || tolower(S[j + i]) == 'u') {
                vowels++;
            }
            if (vowels == 2) {
                words++;
                break;
            }
        }
        vowels = 0;
    }
    return words;
}
