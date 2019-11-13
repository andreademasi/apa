//
// Created by Andrea De Masi on 08/11/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int n;
    char songs[5][255];
} friend;

friend *ReadSongs(int *friends);

int princ_molt(int pos, friend *val, char **sol, int n, int count);

int main() {
    int friends, i;

    friend *proposed_songs = ReadSongs(&friends);

    char **sol = malloc(friends * sizeof(char *));
    for (i = 0; i < friends; i++)
        sol[i] = malloc(255 * sizeof(char));

    printf("Ci sono %d soluzioni", princ_molt(0, proposed_songs, sol, friends, 0));

    free(proposed_songs);
    for (i = 0; i < friends; i++)
        free(sol[i]);
    free(sol);
}

friend *ReadSongs(int *friends) {
    FILE *fp;
    int songs, i, j = 0;

    fp = fopen("/home/andrea/apa/Lab_05/brani.txt", "r");

    fscanf(fp, "%d", friends);

    friend *proposed_songs = malloc(*friends * sizeof(friend));

    while (fscanf(fp, "%d", &songs) != EOF) {
        for (i = 0; i < songs; i++)
            fscanf(fp, "%s", proposed_songs[j].songs[i]);
        proposed_songs[j].n = songs;
        j++;
    }
    return proposed_songs;
}

int princ_molt(int pos, friend *val, char **sol, int n, int count) {
    int i;
    if (pos >= n) {
        printf("Playlist %d:\n", count + 1);
        for (i = 0; i < n; i++)
            printf("%s ", sol[i]);
        printf("\n");
        return count + 1;
    }
    for (i = 0; i < val[pos].n; i++) {
        strcpy(sol[pos], val[pos].songs[i]);
        count = princ_molt(pos + 1, val, sol, n, count);
    }
    return count;
}