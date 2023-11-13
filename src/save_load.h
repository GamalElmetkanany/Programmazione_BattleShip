#ifndef SAVE_LOAD_H_
#define SAVE_LOAD_H_
#include "map.h"
#include "game.h"
#include "ship.h"
#include "all_ships.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE* Save_Game(FILE *pf, game partita);
game Load_Game(FILE *pf, game partita,char filename[128]);
game CaricaMatrixBoard(game partita, int* x, int* y, int length, bool player);
game CaricaMatrixShots(game partita, int* x, int* y, int length, char value, bool player);
game CaricaAbilita(game partita, skills varianti, bool player);
game CaricaContNavi(game partita, int cont, bool player);
game CaricaContTurni(game partita, int cont, bool player);
game CaricaAllShips(game partita, char line[256], bool player);
game CaricaNavi_Load(game partita, FILE* pf);
FILE* Save_Game_Ship(FILE *pf, game partita, map *mappa);
game Load_Game_Ship(FILE *pf, game partita);

#endif /* SAVE_LOAD_H_ */