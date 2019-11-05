//
// Created by Andrea De Masi on 02/11/19.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *cercaRegexp(char *src, char *regexp);

int main() {
    int const dim = 51;
    char string[dim], regexp[dim], *c;

    printf("Inserire stringa: ");
    fgets(string, dim, stdin);
    printf("\nInserire espressione regolare: ");
    scanf("%s", regexp);

    c = cercaRegexp(string, regexp);

    if (c == NULL)
        printf("\nEspressione non trovata.");
    else
        printf("%s", c);
}

char *cercaRegexp(char *src, char *regexp) {
    int i, j, k, m, n = 0, foundk, len = (int) strlen(src), explen = (int) strlen(regexp);

    for (i = 0; i < len; i++) {
        for (j = 0, m = i, n = 0; j < explen; j++) {
            if (src[i + j] == regexp[n]) {
                m++;
                n++;
                if (n == explen - 1)
                    return src + i;
                continue;
            } else if (regexp[n] == '.') {
                m++;
                n++;
                if (j == explen - 1)
                    return src + i;
                continue;
            } else if (regexp[n] == '[') {
                if (regexp[n + 1] != '^') {
                    k = 0;
                    foundk = 0;
                    while (regexp[n + k] != ']') {
                        if (src[i + j] == regexp[n + k]) {
                            foundk = 1;
                            m++;
                        }
                        k++;
                    }
                    n += k + 1;
                    if (n == explen - 1)
                        return src + i;
                    if (foundk == 0)
                        break;
                } else {
                    k = 0;
                    foundk = 0;
                    while (regexp[n + k + 2] != ']') {
                        if (src[i + j] == regexp[n + k + 2]) {
                            foundk = 1;
                            m++;
                        }
                        k++;
                    }
                    n += k + 3;
                    if (n == explen - 1)
                        return src + i;
                    if (foundk == 1)
                        break;
                }
            } else if (regexp[n] == '\\' && regexp[n + 1] == 'a') {
                if (!islower(src[i + j]))
                    break;
                if (j == explen - 1)
                    return src + i;
                n += 2;
            } else if (regexp[n] == '\\' && regexp[n + 1] == 'A') {
                if (!isupper(src[i + j]))
                    break;
                if (j == explen - 1)
                    return src + i;
                n += 2;
            } else {
                break;
            }
        }
    }
    return NULL;
}

