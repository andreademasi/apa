#include <stdlib.h>
#include <stdio.h>

#include "date.h"
#include "titolo_collection.h"
#include "quotation_collection.h"

void FileRead(char *fin, titoli_collection LISTtitoli) {
    char cod[LEN], date[DATELEN], trash[DATELEN];
    int quote = 0, i, amount;
    float value;
    Titolo t;
    FILE *fp = fopen(fin, "r");
    if (fp == NULL)
        return;

    while (fscanf(fp, "%s %d\n", cod, &quote) == 2) {
        t = Search_TitoliCollection(LISTtitoli, cod);
        if (t == NULL) {
            t = TITOLOnew(cod);
            Insert_TitoliCollection(LISTtitoli, t);
        }

        for (i = 0; i < quote; i++) {
            fscanf(fp, "%s %s %f %d\n", date, trash, &value, &amount);
            TITOLOaddTransaction(t, DATEload(date), value, amount);
        }
    }

    fclose(fp);
}

void stampaMenu(char *scelte[], int *selezione) {
    int i = 0;
    printf("\n");
    for (i = 0; i < 8; i++)
        printf("%d > %s\n", i, scelte[i]);
    scanf(" %d", selezione);
}

int main(int argc, char **argv) {
    char *scelte[] = {
            "Uscita",
            "Leggi file",
            "Stampa collezione titoli",
            "Stampa titolo",
            "Stampa quotazione",
            "Stampa MIN/MAX assoluti",
            "Stampa MIN/MAX intervallo",
            "Bilanciamento alberi"
    };

    titoli_collection titoli = Init_TitoliCollection();
    Titolo t;
    Quotation q;
    float f1, f2;
    char temp_1[LEN], temp_2[LEN];
    int selezione = 0, exit = 0;

    FileRead("C:\\Users\\andre\\apa\\Lab_11\\F1.txt", titoli);
    FileRead("C:\\Users\\andre\\apa\\Lab_11\\F2.txt", titoli);
    FileRead("C:\\Users\\andre\\apa\\Lab_11\\F3.txt", titoli);

    do {
        stampaMenu(scelte, &selezione);
        switch (selezione) {

            case 0: {
                exit = 1;
            }
                break;

            case 1: {
                printf("Inserire nome file: ");
                scanf("%s", temp_1);
                FileRead(temp_1, titoli);
            }
                break;

            case 2: {
                Print_TitoliCollection(titoli, stdout);
            }
                break;

            case 3: {
                printf("Inserire codice titolo: ");
                scanf("%s", temp_1);
                t = Search_TitoliCollection(titoli, temp_1);
                if (t != NULL)
                    TITOLOprint(stdout, t);
            }
                break;

            case 4: {
                printf("Inserire codice titolo: ");
                scanf("%s", temp_1);
                t = Search_TitoliCollection(titoli, temp_1);
                if (t != NULL) {
                    printf("Inserire data: ");
                    scanf("%s", temp_1);
                    q = TITOLOquotation(t, DATEload(temp_1));
                    QUOTATIONprint(stdout, q);
                }
            }
                break;

            case 5: {
                printf("Inserire codice titolo: ");
                scanf("%s", temp_1);
                t = Search_TitoliCollection(titoli, temp_1);
                if (t != NULL)
                    printf("MIN = %f || MAX = %f\n", TITOLOmin(t), TITOLOmax(t));
            }
                break;

            case 6: {
                printf("Inserire codice titolo: ");
                scanf("%s", temp_1);
                t = Search_TitoliCollection(titoli, temp_1);
                if (t != NULL) {
                    printf("Inserire data 1: ");
                    scanf("%s", temp_1);
                    printf("Inserire data 2: ");
                    scanf("%s", temp_2);
                    TITOLOinRangeminmax(t, DATEload(temp_1), DATEload(temp_2), &f1, &f2);
                    printf("MIN = %f || MAX = %f\n", f1, f2);
                }
            }
                break;

            case 7: {
                printf("Inserire codice titolo: ");
                scanf("%s", temp_1);
                t = Search_TitoliCollection(titoli, temp_1);
                if (t != NULL)
                    TITOLOtreeBalance(t);
            }
                break;

            default: {
                printf("Scelta non valida\n");
            }
                break;
        }
    } while (!exit);

    return 0;
}
