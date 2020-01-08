//
// Created by Andrea De Masi on 07/01/2020.
//
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "Graph.h"

typedef enum {
    r_stampa, r_adiacenza, r_lista, r_fine, r_err
} comando_e;

comando_e leggiComando(void);

void selezionaDati(Graph matrix_graph, comando_e cmd);

int main(int argc, char **argv) {

    FILE *fp = fopen(argv[1], "r");

    Graph matrix_graph = GRAPHload(fp);

    selezionaDati(matrix_graph, leggiComando());

    GRAPHfree(matrix_graph);
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"stampa", "adiacenza", "lista", "fine"};
    int i;
    printf("\nInserire comando (stampa/adiacenza/lista/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_stampa;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void selezionaDati(Graph matrix_graph, comando_e cmd) {
    int continua = 1;
    char vertex1[30], vertex2[30], vertex3[30];
    while (continua) {
        switch (cmd) {
            case r_stampa:
                GRAPHstore(matrix_graph, stdout, 0);
                cmd = leggiComando();
                break;
            case r_adiacenza:
                printf("Inserire 3 vertici separati da uno spazio: ");
                scanf("%s %s %s", vertex1, vertex2, vertex3);
                printf("I vertici inseriti%s sono adiacenti a coppie",
                       GRAPHadjacent(matrix_graph, vertex1, vertex2, vertex3) ? "" : " non");
                cmd = leggiComando();
                break;
            case r_lista:
                printf("Generazione lista...\n");
                printf("%s\n", GRAPHmat2list(matrix_graph) ? "Lista generata.\n" : "Errore generazione lista.\n");
                cmd = leggiComando();
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default:
                printf("comando errato\n");
                cmd = leggiComando();
                break;
        }
    }
}
