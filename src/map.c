#include <stdio.h>
#include "map.h"

map scrivere_righe(map mappa,int righe)
{
    mappa.righe = righe;
    return mappa;
}

map scrivere_colonne(map mappa,int colonne)
{
    mappa.colonne = colonne;
    return mappa;
}

int leggere_righe(map mappa)
{
    int righe;
    righe = mappa.righe;
    return righe;
}

int leggere_colonne(map mappa)
{
    int colonne;
    colonne=mappa.colonne;
    return colonne;
}

map scrivere_matrix_board(map mappa, int i, int j, int value)
{
    mappa.matrix_board[i][j] = value;
    return mappa;
}

map scrivere_matrix_shots(map mappa, int i, int j, char value)
{
    mappa.matrix_shots[i][j] = value;
    return mappa;
}

int leggere_matrix_board(map mappa, int i, int j)
{
    return mappa.matrix_board[i][j];
}

char leggere_matrix_shots(map mappa, int i, int j)
{
    return mappa.matrix_shots[i][j];
}