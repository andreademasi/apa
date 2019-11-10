//
// Created by Andrea De Masi on 01/11/19.
//

#include <stdio.h>

int majority(int *a, int N);

int majorityR(int *a, int l, int r);

int main() {
    int V[10] = {1, 1, 1, 2, 2, 2, 2, 2, 2, 1};

    printf("%d", majority(V, 10));
}

int majority(int *a, int N) {
    int l = 0, r = N - 1, i, j = 0;
    int result = majorityR(a, l, r);
    for (i = 0; i < N; i++) {
        if (a[i] == result)
            j++;
        if (j > N / 2)
            return result;
    }
    return -1;
}

int majorityR(int *a, int l, int r) {
    int q = (l + r) / 2, i, occurencies = 0;
    if (r <= l) {
        return a[l];
    }
    int ml = majorityR(a, l, q); // maggioritario a sinistra

    int mr = majorityR(a, q + 1, r); // maggioritario a destra

    for (i = l; i < r; i++) {
        if (a[i] == ml)
            occurencies++;
        if (occurencies > ((r - l) / 2))
            return ml;
    }
    return mr;
}