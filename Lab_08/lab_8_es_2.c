//
// Created by Andrea De Masi on 02/12/19.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char color;
    int value;
} Tube;

typedef struct {
    Tube horizontal;
    Tube vertical;
} Tile;

Tile *openTiles();

Tile **openBoard(Tile *tiles, int *mark);

int disp_sempl(int pos, Tile **sol, int *mark, int count, Tile **board, Tile *tiles);

int tiles_n, rows, columns, best_board_value = 0;
Tile **best_board;

int main() {
    int i, j, *mark;
    Tile *tiles = openTiles();

    mark = calloc(tiles_n, sizeof(int));

    Tile **board = openBoard(tiles, mark);

    Tile **sol = (Tile **) malloc(rows * sizeof(Tile *));
    for (i = 0; i < rows; i++)
        sol[i] = (Tile *) malloc(columns * sizeof(Tile));

    best_board = (Tile **) malloc(rows * sizeof(Tile *));
    for (i = 0; i < rows; i++)
        best_board[i] = (Tile *) malloc(columns * sizeof(Tile));

    disp_sempl(0, sol, mark, 0, board, tiles);

    printf("%d\n", best_board_value);

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%c%d %c%d\t", best_board[i][j].horizontal.color, best_board[i][j].horizontal.value,
                   best_board[i][j].vertical.color,
                   best_board[i][j].vertical.value);
        }
        printf("\n");
    }
}

Tile *openTiles() {
    FILE *fp;
    Tile *tiles;
    int i = 0;

    fp = fopen("C:\\Users\\andre\\apa\\Lab_08\\tiles.txt", "r");

    if (fp == NULL) {
        printf("ERRORE");
        exit(100);
    }

    fscanf(fp, "%d ", &tiles_n);

    tiles = (Tile *) malloc(tiles_n * sizeof(Tile));

    while (fscanf(fp, "%c %d %c %d ", &tiles[i].horizontal.color, &tiles[i].horizontal.value, &tiles[i].vertical.color,
                  &tiles[i].vertical.value) != EOF)
        i++;

    return tiles;
}

Tile **openBoard(Tile *tiles, int *mark) {
    FILE *fp;
    Tile **board;
    int i, j, tile_index, rotation;

    fp = fopen("C:\\Users\\andre\\apa\\Lab_08\\board.txt", "r");

    if (fp == NULL)
        exit(-1);

    fscanf(fp, "%d %d ", &rows, &columns);

    board = (Tile **) malloc(rows * sizeof(Tile *));

    for (i = 0; i < rows; i++)
        board[i] = (Tile *) malloc(columns * sizeof(Tile));

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            board[i][j].horizontal.color = 'X';
            board[i][j].vertical.color = 'X';
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            fscanf(fp, "%d/%d ", &tile_index, &rotation);
            if (tile_index != -1) {
                mark[tile_index] = 1;
                if (rotation != 1)
                    board[i][j] = tiles[tile_index];
                else {
                    board[i][j].vertical = tiles[tile_index].horizontal;
                    board[i][j].horizontal = tiles[tile_index].vertical;
                }
            }
        }
    }

    fclose(fp);
    return board;
}

int disp_sempl(int pos, Tile **sol, int *mark, int count, Tile **board, Tile *tiles) {
    int i, j, r, c, rows_value = 0, columns_value = 0, temp = 0;
    if (pos >= rows * columns) {
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                if (j == 0)
                    temp = sol[i][j].horizontal.value; // salvo il primo valore
                else if (sol[i][j - 1].horizontal.color == sol[i][j].horizontal.color)
                    temp += sol[i][j].horizontal.value; // se la tessera precedente aveva lo stesso colore aggiungo il suo valore
                else {
                    temp = 0; // altrimenti annullo la somma e passo alla riga successiva
                    break;
                }
            }
            rows_value += temp;
        }
        temp = 0;
        for (i = 0; i < columns; i++) {
            for (j = 0; j < rows; j++) {
                if (j == 0)
                    temp = sol[j][i].vertical.value; // salvo il primo valore
                else if (sol[j - 1][i].vertical.color == sol[j][i].vertical.color)
                    temp += sol[j][i].vertical.value; // se la tessera precendente aveva lo stesso colore aggiungo il suo valore
                else {
                    temp = 0; // altrimenti annullo la somma e passo alla colonna successiva
                    break;
                }
            }
            columns_value += temp;
        }
        if (rows_value + columns_value > best_board_value) {
            best_board_value = rows_value + columns_value;
            for (i = 0; i < rows; i++) {
                for (j = 0; j < columns; j++)
                    best_board[i][j] = sol[i][j];
            }
        }
        return count + 1;
    }

    r = pos / columns;
    c = pos % columns;

    for (i = 0; i < tiles_n; i++)
        if (mark[i] == 0) {
            if (board[r][c].horizontal.color == 'X') { // Pedina non presente nella scacchiera
                mark[i] = 1;
                sol[r][c] = tiles[i];
                count = disp_sempl(pos + 1, sol, mark, count, board, tiles);

                sol[r][c].vertical = tiles[i].horizontal; // ruoto la pedina
                sol[r][c].horizontal = tiles[i].vertical;
                count = disp_sempl(pos + 1, sol, mark, count, board, tiles);
                mark[i] = 0;
            } else {
                sol[r][c] = board[r][c]; // Pedina già presente nella scacchiera
                disp_sempl(pos + 1, sol, mark, count, board, tiles);
            }
        }
    return count;
}