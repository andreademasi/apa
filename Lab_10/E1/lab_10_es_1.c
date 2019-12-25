//
// Created by Andrea on 25/12/2019. ( MERRY CHRISTMAS! )
//

#include<stdlib.h>
#include<stdio.h>

int fZ(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);

int fR(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);

int fT(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);

int fS(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);

int ****malloc4d(int z, int r, int t, int s);

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int main() {
    int maxZ, maxR, maxT, maxS, ****Z, ****R, ****S, ****T, z = 19, r = 6, t = 8, s = 5;

    Z = malloc4d(z, r, t, s);
    R = malloc4d(z, r, t, s);
    T = malloc4d(z, r, t, s);
    S = malloc4d(z, r, t, s);

    maxZ = fZ(Z, R, T, S, z, r, t, s);
    maxR = fR(Z, R, T, S, z, r, t, s);
    maxT = fT(Z, R, T, S, z, r, t, s);
    maxS = fS(Z, R, T, S, z, r, t, s);

    printf("Collana massima di lunghezza: %d", max(maxZ, max(maxR, max(maxT, maxS))));
}

int ****malloc4d(int z, int r, int t, int s) {
    int i, j, k, l, ****temp;

    temp = malloc((1 + z) * sizeof(int ***));
    for (i = 0; i <= z; i++) {
        temp[i] = malloc((1 + r) * sizeof(int **));
        for (j = 0; j <= r; j++) {
            temp[i][j] = malloc((1 + t) * sizeof(int *));
            for (k = 0; k <= t; k++) {
                temp[i][j][k] = malloc((1 + s) * sizeof(int));
                for (l = 0; l <= s; l++)
                    temp[i][j][k][l] = -1; // Inizializzo a -1
            }
        }
    }
    return temp;
}

int fZ(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    if (z <= 0)
        return 0;
    if (Z[z][r][t][s] != -1)
        return Z[z][r][t][s];

    // Salvo nella matrice il massimo (+1) tra la collana iniziante con lo zaffiro e quella iniziante per rubino e ritorno
    return Z[z][r][t][s] = 1 + max(fZ(Z, R, T, S, z - 1, r, t, s), fR(Z, R, T, S, z - 1, r, t, s));
}

int fR(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    if (r <= 0)
        return 0;
    if (R[z][r][t][s] != -1)
        return R[z][r][t][s];

    return R[z][r][t][s] = 1 + max(fS(Z, R, T, S, z, r - 1, t, s), fT(Z, R, T, S, z, r - 1, t, s));
}

int fT(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    if (t <= 0)
        return 0;
    if (T[z][r][t][s] != -1)
        return T[z][r][t][s];

    return T[z][r][t][s] = 1 + max(fZ(Z, R, T, S, z, r, t - 1, s), fR(Z, R, T, S, z, r, t - 1, s));
}

int fS(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    if (s <= 0)
        return 0;
    if (S[z][r][t][s] != -1)
        return S[z][r][t][s];

    return S[z][r][t][s] = 1 + max(fS(Z, R, T, S, z, r, t, s - 1), fT(Z, R, T, S, z, r, t, s - 1));
}