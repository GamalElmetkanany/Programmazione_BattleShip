#include "game.h"
#include "generics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

game Init_All(game partita, bool load) {
	char filename[128];
	FILE* pf;
	skills abilita;
	all_ships allships;
	
	partita = scrivere_mappa_gioc1(partita, Init_Map(leggere_mappa_gioc1(partita)));
	partita = scrivere_mappa_gioc2(partita, Init_Map(leggere_mappa_gioc2(partita)));

	partita = scrivere_player1(partita, 1);
	partita = scrivere_player2(partita, 2);

	partita = scriverecontatore1(partita, 0);
	partita = scriverecontatore2(partita, 0);

	partita = scrivere_navi1(partita, 35);
	partita = scrivere_navi2(partita, 35);

	abilita = scrivere_bombardamento_aereo(abilita, 1);
	abilita = scrivere_colpo_largo_raggio(abilita, 3);
	abilita = scrivere_radar(abilita, 3);
	partita = scriverevariante1(partita, abilita);
	partita = scriverevariante2(partita, abilita);

	allships = scrivere_cont1(allships, 0);
	allships = scrivere_cont2(allships, 0);
	allships = scrivere_cont3(allships, 0);
	allships = scrivere_cont4(allships, 0);
	allships = scrivere_cont5(allships, 0);
	partita = scrivere_all_ships1(partita, allships);
	partita = scrivere_all_ships2(partita, allships);

	if(load) {
		system("cls");
		printf("Turno del Giocatore 1\n---------------------\n");
		system("pause");
		partita = scrivereturno(partita, true);
		partita = Carica_Navi(partita, pf, true, 1, 0 ,5);
		system("cls");
		printf("Turno del Giocatore 2\n---------------------\n");
		system("pause");
		partita = scrivereturno(partita, !(leggereturno(partita)));
		partita = Carica_Navi(partita, pf, false, 1, 0 ,5);
		partita = scrivereturno(partita, !(leggereturno(partita)));
		system("cls");
	}

	return partita;
}

game scrivere_player1(game partita, int player1)
{
	partita.player1=player1;
	return partita;
}

game scrivere_player2(game partita, int player2)
{
	partita.player2=player2;
	return partita;
}

game scrivere_navi1(game partita, int navi) {
    partita.ships1 = navi;
    return partita;
}

game scrivere_navi2(game partita, int navi) {
    partita.ships2 = navi;
    return partita;
}

game scrivere_mappa_gioc1(game partita, map mappa_gioc1)
{
	partita.mappa_gioc1=mappa_gioc1;
	return partita;
}

game scrivere_mappa_gioc2(game partita, map mappa_gioc2)
{
	partita.mappa_gioc2=mappa_gioc2;
	return partita;
}

game scrivereturno(game partita, bool turno)
{
	partita.turno=turno;
	return partita;
}

game scriverecontatore1(game partita, int contatore_turni)
{
	partita.contatore_turni1 = contatore_turni;
	return partita;
}

game scriverecontatore2(game partita, int contatore_turni)
{
	partita.contatore_turni2 = contatore_turni;
	return partita;
}

game scriverevariante1(game partita, skills variante)
{
	partita.variante1=variante;
	return partita;
}

game scriverevariante2(game partita, skills variante)
{
	partita.variante2=variante;
	return partita;
}

game scrivere_filename(game partita, const char *filename) {
	partita.filename = filename;
	return partita;
}

game scrivere_all_ships1(game partita,all_ships all_ships1)
{
	partita.all_ships1=all_ships1;
	return partita;
}

game scrivere_all_ships2(game partita,all_ships all_ships2)
{
	partita.all_ships2=all_ships2;
	return partita;
}
/* --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* LEGGERE ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------------------------------------------------------------------- */
all_ships leggere_all_ships1(game partita)
{
	return partita.all_ships1;
}

all_ships leggere_all_ships2(game partita)
{
	return partita.all_ships2;
}

int leggere_player1( game partita )
{
	return partita.player1;
}

int leggere_player2( game partita )
{
	return partita.player2;
}

int leggere_navi1(game partita) {
    return partita.ships1;
}

int leggere_navi2(game partita) {
    return partita.ships2;
}

map leggere_mappa_gioc1(game partita)
{
	return partita.mappa_gioc1;
}

map leggere_mappa_gioc2(game partita)
{
	return partita.mappa_gioc2;
}

bool leggereturno(game partita)
{
	return partita.turno;
}

int leggerecontatore1(game partita)
{
	return partita.contatore_turni1;
}

int leggerecontatore2(game partita)
{
	return partita.contatore_turni2;
}

skills leggerevariante1(game partita)
{
	return partita.variante1;
}

skills leggerevariante2(game partita)
{
	return partita.variante2;
}

const char* leggere_filename(game partita) {
	return partita.filename;
}

game assegna_mappa_gioc1(game partita, map mappaNew) {
	partita.mappa_gioc1 = mappaNew;
	return partita;
}

game assegna_mappa_gioc2(game partita, map mappaNew) {
	partita.mappa_gioc2 = mappaNew;
	return partita;
}