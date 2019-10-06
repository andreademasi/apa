//
// Created by Andrea De Masi on 05/10/19.
//

#include <stdio.h>
#include <string.h>

int main() {

    FILE *source_pointer;
    FILE *dictionary_pointer;
    FILE *coded_pointer;
    char string[201];
    char coded_string[201];
    int i = 0, j = 0, k = 0, m = 0, n = 0, entries;
    typedef struct {
        char code[10];
        char word[20];
    } Dictionary;

    Dictionary dictionary[30];

    dictionary_pointer = fopen("/home/andrea/apa/Lab_01/dizionario.txt", "r");
    source_pointer = fopen("/home/andrea/apa/Lab_01/sorgente.txt", "r");
    coded_pointer = fopen("/home/andrea/apa/Lab_01/ricodificato.txt", "w+");

    fscanf(dictionary_pointer, "%d\n", &entries);

    while (fscanf(dictionary_pointer, "%s %s\n", dictionary[i].code, dictionary[i].word) != EOF) {
        i++;
    }

    /*
     * k = contatore del carattere considerato nella stringa sorgente
     * i = contatore delle "entrate" del dizionario
     * j = contatore carattere considerato della "parola" del dizionario
     * m = contatore caratteri della stringa codificata
     * n = contatore carattere considerato del codice del dizionario
     */

    while (fgets(string, 201, source_pointer) != NULL) { //acquisisco stringa
        for (k = 0; k < strlen(string); k++) { //valuto il singolo carattere
            for (i = 0; i < entries; i++) { //cerco nel dizionario le possibili corrispondenze
                while (dictionary[i].word[j] != '\0') {
                    if (string[k + j] !=
                        dictionary[i].word[j]) { //se il carattere non corrisponde esco e vado alla parola del dizionario successiva
                        j = 0;
                        break;
                    } else if (string[k + j] == dictionary[i].word[j]) { //se corrisponde vedo la lettera successiva
                        j++;
                        if (j == strlen(dictionary[i].word)) { //se ho finito di controllare con successo, codifico
                            while (dictionary[i].code[n] != '\0') { //sostituisco i singoli caratteri
                                coded_string[m] = dictionary[i].code[n];
                                n++;
                                m++;
                            }
                            n = 0;
                            k += j; //tengo conto di quanti caratteri ho sostituito
                            j = 0;
                        }
                    }
                }
            }
            coded_string[m] = string[k]; //se non viene trovata nessuna corrispondenza, copia il carattere nella stringa codificata
            m++;
        }
        coded_string[m + 1] = '\0';
        fprintf(coded_pointer, "%s", coded_string);
        m = 0;
    }
    return 0;
}

