//
// Created by Andrea De Masi on 28/10/19.
//

#include <stdio.h>

int gcd(int a, int b);

int isEven(int n);

int main() {
    int a, b, res;

    printf("Inserire a e poi b:");
    scanf("%d", &a);
    scanf("%d", &b);

    res = gcd(a, b);

    res == 1 ? printf("\nI numeri sono coprimi") : printf("\nMCD: %d", res);
}

int isEven(int n) {
    if (n % 2 == 0)
        return 1;
    return 0;
}

int gcd(int a, int b) {

    if (a < b) {
        int tmp = a;
        a = b;
        b = tmp;
    }
    if (a % b == 0)
        return b;

    int evenA = isEven(a), evenB = isEven(b);

    if (evenA && evenB) // Entrambi pari
        return 2 * gcd(a / 2, b / 2);
    else if (!evenA && evenB)  // Entrambi dispari
        return gcd(a, b / 2);
    else if (!evenA) // A è dispari
        return gcd((a - b) / 2, b);
    return gcd(a / 2, b); // A è pari
}