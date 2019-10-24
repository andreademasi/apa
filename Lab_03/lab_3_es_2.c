//
// Created by Andrea De Masi on 19/10/19.
//
#include <stdio.h>

void stampaCodifica(void *p, int size, int bigEndian);

void toBinary(unsigned char *f, int *bit, int j, int l);

void stampaBit(int *v, int n, int size);

int main() {
    float af;
    double ad;
    long double ald;
    int bigEndian = 0;
    unsigned int i = 1;

    char *c = (char *) &i;
    if (*c)
        bigEndian = 0;
    else
        bigEndian = 1;

    scanf("%Lf", &ald);
    ad = (double) ald;
    af = (float) ald;

    stampaCodifica((void *) &af, sizeof(af), bigEndian);
    stampaCodifica((void *) &ad, sizeof(ad), bigEndian);
    stampaCodifica((void *) &ald, sizeof(ald), bigEndian);

    return 0;
}

void stampaCodifica(void *p, int size, int bigEndian) {

    unsigned char f[4];
    unsigned char d[8];
    unsigned char ld[16];
    int bit[size * 8];
    int i, j, k = 1;

    for (i = 0; i < size * 8; i++)
        bit[i] = 0;

    if (size == 4) {
        printf("***FLOAT***\n");
        for (i = 0; i < size; i++)
            *(f + i) = *((unsigned char *) (p + i));
        if (bigEndian) {
            for (j = 0; j < size - 1; j++) {
                toBinary(f, bit, j, 0);
            }
        } else {
            for (j = size - 1; j >= 0; j--) {
                toBinary(f, bit, j, 8 * k - 1);
                k++;
            }
        }
    } else if (size == 8) {
        printf("\n***DOUBLE***\n");
        for (i = 0; i < size; i++)
            *(d + i) = *((unsigned char *) (p + i));
        if (bigEndian) {
            for (j = 0; j < size - 1; j++) {
                toBinary(d, bit, j, 0);
            }
        } else {
            for (j = size - 1; j >= 0; j--) {
                toBinary(d, bit, j, 8 * k - 1);
                k++;
            }
        }
    } else if (size == 16) {
        printf("\n***LONG DOUBLE***\n");
        for (i = 0; i < size; i++)
            *(ld + i) = *((unsigned char *) (p + i));
        if (bigEndian) {
            for (j = 0; j < size - 1; j++) {
                toBinary(ld, bit, j, 0);
            }
        } else {
            for (j = size - 1; j >= 0; j--) {
                toBinary(ld, bit, j, 8 * k - 1);
                k++;
            }
        }
    }
    stampaBit(bit, size * 8, size);
}

void stampaBit(int *v, int n, int size) {
    int i;
    if (size == 4) {
        for (i = 0; i < n; i++, v++) {
            if (i == 0)
                printf("Bit segno: ");
            if (i == 1)
                printf("\nBit esponente: ");
            if (i == 9)
                printf("\nBit mantissa: ");
            printf("%d", *v);
        }
    } else if (size == 8) {
        for (i = 0; i < n; i++, v++) {
            if (i == 0)
                printf("Bit segno: ");
            if (i == 1)
                printf("\nBit esponente: ");
            if (i == 12)
                printf("\nBit mantissa: ");
            printf("%d", *v);
        }
    } else if (size == 16) {
        for (i = 0; i < n; i++, v++) {
            if (i == 0)
                printf("Bit segno: ");
            if (i == 1)
                printf("\nBit esponente: ");
            if (i == 16)
                printf("\nBit mantissa: ");
            printf("%d", *v);
        }
    }
}

void toBinary(unsigned char *f, int *bit, int j, int l) {
    int i = 0;
    do {
        bit[l - i] = f[j] % 2;
        f[j] = f[j] / 2;
        if (l == 0)
            i--;
        else
            i++;
    } while (f[j] > 0);
}