#ifndef GENERICS_H_
#define GENERICS_H_
#define ASCII_ESC 27

#include "map.h"
#include "ship.h"
#include "game.h"
#include "skills.h"
#include "save_load.h"
#include "all_ships.h"
#include <stdbool.h>
#include <stdio.h>



/* SOTTOFUNZIONI */
int MenuPrincipale();
int Menu(game partita);
void clrScreen();
void Show_Map(map mappa);
void ShowMapShots(map mappa);
game Carica_Navi(game partita, FILE *pf, bool player, int size, int i, int n);
game Insert_Nave(ship *nave, map *mappa, int i, game partita, FILE *pf);
game AggiornaContNavi(game partita, int numvolte);
bool LeggereNave5(bool load,game partita,FILE *pf);
bool ctrl_Pos(map mappa, ship nave, int x, int y);
bool ctrlSpace(int riga, int colonna, int verso, int size);
int CharToNum(char value);
char NumToChar(int num);
void FinePartita(int player, const char* filename);


#endif /* GENERICS_H_ */
