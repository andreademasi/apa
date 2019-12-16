//
// Created by Andrea De Masi on 14/12/2019.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inizio;
    int fine;
} att;

att *openFile(int *activities_n);

void quicksort(att *val, int n);

void solveDP(att *val, int n);

int main() {
    int activities_n;

    att *activities = openFile(&activities_n);
    quicksort(activities, activities_n);

    solveDP(activities, activities_n);
    free(activities);
}

void swap(att *val, int a, int b) {
    att tmp;
    tmp = val[a];
    val[a] = val[b];
    val[b] = tmp;
}

int partition(att *val, int l, int r) {
    int i = l - 1, j = r;
    att x = val[r];
    for (;;) {
        while (val[++i].fine < x.fine);
        while (val[--j].fine > x.fine)
            if (j == l)
                break;
        if (i >= j)
            break;
        swap(val, i, j);
    }
    swap(val, i, r);
    return i;
}

void quicksortR(att *val, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = partition(val, l, r);
    quicksortR(val, l, q - 1);
    quicksortR(val, q + 1, r);
}

void quicksort(att *val, int n) {
    int l = 0, r = n - 1;
    quicksortR(val, l, r);
}

att *openFile(int *activities_n) {
    att *activities;
    FILE *fp;
    int i = 0;

    if ((fp = fopen("C:\\Users\\Andrea\\apa\\Lab_09\\att.txt", "r")) == NULL) {
        printf("ERRORE APERTURA FILE");
        exit(99);
    }

    fscanf(fp, "%d", activities_n);

    activities = malloc(*activities_n * sizeof(att));
    while (fscanf(fp, "%d %d", &activities[i].inizio, &activities[i].fine) != EOF)
        i++;

    return activities;
}

void LISprint(att *val, int *P, int i) {
    if (P[i] == -1) {
        printf("inizio: %d fine: %d\t", val[i].inizio, val[i].fine);
        return;
    }
    LISprint(val, P, P[i]);
    printf("inizio: %d fine: %d\t", val[i].inizio, val[i].fine);
}

void solveDP(att *val, int n) {
    int i, j, ris = 1, last = 1, *L, *P;
    L = malloc(n * sizeof(int));
    P = malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        L[i] = 0;
        P[i] = -1;
        for (j = 0; j < i; j++)
            if (val[i].inizio >= val[j].fine && L[i] < L[j] + (val[j].fine - val[j].inizio)) {
                L[i] += val[j].fine - val[j].inizio;
                P[i] = j;
            }
        if (ris <= L[i]) {
            ris = L[i];
            last = i;
        }
    }
    printf("Sequence is:\n");
    LISprint(val, P, last);
    printf("\nLength: %d", ris);
    free(L);
    free(P);
}
