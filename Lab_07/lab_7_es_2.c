//
// Created by Andrea De Masi on 25/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char type;
    int amount;
    int value;
} Gem;

typedef struct {
    char *necklace;
    int value;
    int amount;
} temp_sol;

temp_sol disp_rip(int pos, Gem gems[], char *sol, temp_sol temp, int n, int k, int count, int max_rip);

int pruning(const char *sol, int i, char value, int max_rip);

int main() {
    int z, s, r, t, i, max_rip, n, val_z, val_s, val_t, val_r;
    temp_sol initial, temp, best;
    char *sol;
    FILE *fp = fopen("/home/andrea/apa/Lab_07/e2_test_set.txt", "r");
    fscanf(fp, "%d", &n);
    n = 1;
    while (fscanf(fp, "%d %d %d %d %d %d %d %d %d", &z, &r, &t, &s, &val_z, &val_r, &val_t, &val_s, &max_rip) != EOF) {

        initial.value = 0;
        best.value = 0;
        initial.necklace = malloc(z + s + r + t + 1 * sizeof(char));
        best.necklace = malloc(z + s + r + t + 1 * sizeof(char));
        sol = malloc(z + s + r + t * sizeof(char));

        Gem gems[4] = {'Z', z, val_z, 'S', s, val_s, 'R', r, val_r, 'T', t, val_t};

        for (i = 1; i < z + s + r + t; i++) {
            temp = disp_rip(0, gems, sol, initial, 4, i, 0, max_rip);
            if (temp.value > best.value) {
                best.value = temp.value;
                best.amount = temp.amount;
                strcpy(best.necklace, temp.necklace);
            }
        }
        printf("\nTEST #%d\n", n);
        printf("zaffiro = %d [%d], rubino = %d [%d], topazio = %d [%d], smeraldo = %d [%d], TOT = %d {max_rip = %d}",
               z, val_z, r, val_r, t, val_t, s, val_s, z + r + t + s, max_rip);
        printf("\nSoluzione ottima di valore %d usando %d gemma/e\n"
               "Composizione collana: %s", best.value, best.amount,
               best.necklace);
        n++;
        free(initial.necklace);
        free(best.necklace);
        free(sol);
    }
}

temp_sol disp_rip(int pos, Gem gems[], char *sol, temp_sol temp, int n, int k, int count, int max_rip) {
    int i, n_s = 0, n_z = 0, n_r = 0, n_t = 0, current_value = 0;
    if (pos >= k) {
        for (i = 0; i < k; i++) {
            switch (sol[i]) {
                case 'Z':
                    n_z++;
                    break;
                case 'S':
                    n_s++;
                    break;
                case 'T':
                    n_t++;
                    break;
                case 'R':
                    n_r++;
                    break;
            }
        }
        if (n_z <= n_s) {
            for (i = 0; i < k; i++)
                current_value = gems[0].value * n_z + gems[1].value * n_s + gems[2].value * n_r + gems[3].value * n_t;
            if (temp.value < current_value) {
                temp.value = current_value;
                temp.amount = n_r + n_s + n_t + n_z;
                for (i = 0; i < k; i++)
                    temp.necklace[i] = sol[i];
            }
        }
        return temp;
    }
    for (i = 0; i < n; i++) {
        if (gems[i].amount > 0 && !pruning(sol, pos - 1, gems[i].type, max_rip)) { // PRUNING
            sol[pos] = gems[i].type;
            gems[i].amount--;
            temp = disp_rip(pos + 1, gems, sol, temp, n, k, count, max_rip);
            gems[i].amount++;
        }
    }
    return temp;
}

int pruning(const char *sol, int i, char value, int max_rip) {
    int j, count = 0;
    if (i + 1 >= max_rip) {
        for (j = 0; j <= max_rip; j++) {
            if (sol[i - j] == sol[i])
                count++;
            else
                break;
        }
        if (count >= max_rip && sol[i] == value)
            return 1;
    }
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
