#include <stdio.h>
#include <stdlib.h>

int main()
{
    int campionato[20][20], giornata, i = 0, j = 0, righe, colonne;
    char c;
    FILE* f;

    if((f = fopen("campionato.txt", "r")) == NULL){
        printf("Errore file");
        return 1;
    }

    while(fscanf(f,"%d%c", &giornata, &c) != EOF){
        if(c == '\n'){
            campionato[i][j] = giornata;
            i++;
            righe = i + 1;
            colonne = j + 1;
            j = 0;
        }
        else{
            campionato[i][j] = giornata;
            j++;
        }
    }

    fclose(f);
    return 0;
}
