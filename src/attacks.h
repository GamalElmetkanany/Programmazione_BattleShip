#ifndef ATTACKS_H_
#define ATTACKS_H_
#define ASCII_ESC 27

#include "map.h"
#include "game.h"
#include <stdbool.h>

/* SOTTOFUNZIONI */
void clrScreen(int);
int ctrlTipologiaDisp(skills abilita, int *tipologia, int contatoreturni);
bool ctrl_att(map mappa,int x,int y);
bool ctrl_att2(map mappaAvv, map mappaMia, int x, int y, int *verso);
void aggiorna_affondi(map *mappa, game *partita, int x, int y, int verso);

/* ATTACCHI */
void attacco(map mappaAvv, map *mappaMia, game *partita);
void Attacco_Semplice(map mappaAvv, map *mappaMia, game *partita, int x, int y);
void Attacco_Radar(map mappaAvv, map *mappaMia, game *partita);
void Attacco_Largo_Raggio(map mappaAvv, map *mappaMia, game *partita);
void Attacco_Bombardamento(map mappaAvv, map *mappaMia, game *partita);
int LeggiTipologiaAtt(game partita);
void LeggiXY(map mappa, int *x, int *y);

#endif /* ATTACKS_H_ */
