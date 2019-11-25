//
// Created by Andrea De Masi on 22/11/19.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char type;
    int amount;
} Gem;

int disp_rip(int pos, Gem val[], char *sol, int n, int k, int count);

int pruning(const char *sol, int i, char value);

int main() {
    int z = 3, s = 10, r = 1, t = 6, i, temp, count = 0;
    char *sol;
    Gem val[4] = {'Z', z, 'S', s, 'R', r, 'T', t};

    sol = malloc((t + s + z + r) * sizeof(char));

    for (i = 0; i < z + s + r + t; i++) {
        temp = disp_rip(0, val, sol, 4, i, 0);
        if (temp == 1)
            count++;
    }
    printf("Lunghezza massima collana: %d\n", count - 1);
}

int disp_rip(int pos, Gem val[], char *sol, int n, int k, int count) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++)
            printf("%c ", sol[i]);
        printf("\n");
        return count = 1;
    }
    for (i = 0; i < n; i++) {
        if (pos == 0) {
            sol[pos] = val[i].type;
            val[i].amount--;
            count = disp_rip(pos + 1, val, sol, n, k, count);
            val[i].amount++;
        }
        if (val[i].amount > 0 && !pruning(sol, pos - 1, val[i].type)) { // PRUNING
            sol[pos] = val[i].type;
            val[i].amount--;
            count = disp_rip(pos + 1, val, sol, n, k, count);
            val[i].amount++;
        }
    }
    return count;
}

int pruning(const char *sol, int i, char value) {
    switch (sol[i]) {
        case 'Z':
            if (value != 'Z' && value != 'R')
                return 1;
            return 0;
        case 'S':
            if (value != 'S' && value != 'T')
                return 1;
            return 0;
        case 'R':
            if (value != 'S' && value != 'T')
                return 1;
            return 0;
        case 'T':
            if (value != 'Z' && value != 'R')
                return 1;
            return 0;
    }
    return 0;
}
