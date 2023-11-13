#ifndef GAME_H_
#define GAME_H_

//#include "generics.h"
#include "map.h"
#include "skills.h"
#include "all_ships.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	all_ships all_ships1;
	all_ships all_ships2;
	int player1;
	int player2;
    int ships1;
    int ships2;
	map mappa_gioc1;
	map mappa_gioc2;
	bool turno;
	int contatore_turni1;
    int contatore_turni2;
	skills variante1;
	skills variante2;
	const char *filename;
} game;

game Init_All(game partita, bool load);
map Init_Map(map mappa);
game scrivere_all_ships1(game partita,all_ships all_ships1);
game scrivere_all_ships2(game partita,all_ships all_ships2);
game scrivere_player1( game partita, int player1);
game scrivere_player2( game partita, int player2);
game scrivere_navi1(game partita, int navi);
game scrivere_navi2(game partita, int navi);
game scrivere_mappa_gioc1(game partita, map mappa_gioc1);
game scrivere_mappa_gioc2(game partita, map mappa_gioc2);
game scrivereturno(game partita, bool turno);
game scriverecontatore1(game partita, int contatore_turni);
game scriverecontatore2(game partita, int contatore_turni);
game scriverevariante1(game partita, skills variante);
game scriverevariante2(game partita, skills variante);
game scrivere_filename(game partita, const char *filename);

all_ships leggere_all_ships1(game partita);
all_ships leggere_all_ships2(game partita);
int leggere_player1( game partita );
int leggere_player2( game partita );
int leggere_navi1(game partita);
int leggere_navi2(game partita);
map leggere_mappa_gioc1(game partita);
map leggere_mappa_gioc2(game partita);
bool leggereturno(game partita);
int leggerecontatore1(game partita);
int leggerecontatore2(game partita);
skills leggerevariante1(game partita);
skills leggerevariante2(game partita);
const char* leggere_filename(game partita);

game assegna_mappa_gioc1(game partita, map mappaNew);
game assegna_mappa_gioc2(game partita, map mappaNew);


#endif /* GAME_H_ */
