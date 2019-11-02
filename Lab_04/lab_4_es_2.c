//
// Created by Andrea De Masi on 01/11/19.
//

#include <stdio.h>

int majority(int *a, int N);

struct m { // m = elemento maggioritario
    int n;
    int occurrencies;
};

struct m majorityR(int *a, int l, int r);

int main() {
    int V[8] = {0, 1, 0, 2, 3, 4, 0, 5};

    printf("%d", majority(V, 8));
}

int majority(int *a, int N) {
    int l = 0, r = N - 1, i, j = 0;
    struct m result = majorityR(a, l, r);
    for (i = 0; i < N; i++) {
        if (a[i] == result.n)
            j++;
        if (j > N / 2)
            return result.n;
    }
    return -1;
}

struct m majorityR(int *a, int l, int r) {
    int q = (l + r) / 2;
    if (r <= l) {
        struct m n = {a[l], 1};
        return n;
    }
    struct m ml = majorityR(a, l, q); // maggioritario a sinistra
    struct m mr = majorityR(a, q + 1, r); // maggioritario a destra
    if (ml.n == mr.n) { // se il maggioritario è lo stesso sommo le occorrenze
        ml.occurrencies += mr.occurrencies;
        return ml;
    } else if (ml.occurrencies > mr.occurrencies) //altrimenti seleziono il nuovo maggioritario
        return ml;
    else if (mr.occurrencies > ml.occurrencies)
        return mr;
    ml.n = -1; // se non c'è un maggioritario nel sottovettore
    ml.occurrencies = 0;
    return ml;
}