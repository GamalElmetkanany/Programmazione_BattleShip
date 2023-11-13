#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define RIGHE 16
#define COLONNE 16

/* MODULI */
#include "generics.h"
#include "attacks.h"
#include "game.h"
#include "save_load.h"



int main()
{
	FILE *pf;
	game partita;
	map map_p1, map_p2;
	int scelta, choice, player;
	char conferma;
	all_ships ship1,ship2;

	char filen[128];
	


	printf(" --- BENVENUTI AL GIOCO DELLA BATTAGLIA NAVALE ---\n\n");
	Principale:
	do {
		scelta = MenuPrincipale();
		switch (scelta) {
			case 1:
				system("cls");
				printf("Scegliere un nome per il salvataggio:\n");
				scanf("%14s",filen);
				strcat(filen,".txt");
				partita = scrivere_filename(partita, filen);
				pf=fopen(leggere_filename(partita),"w");
				fclose(pf);
                partita = Init_All(partita, true);

				pf=Save_Game(pf,partita);
				MenuSecondario:

				map_p1 = leggere_mappa_gioc1(partita);
				map_p2 = leggere_mappa_gioc2(partita);
				do {
					if(leggereturno(partita))
						player = 1;
					else
						player = 2;
					system("cls");
					printf("Turno del Giocatore %d\n---------------------\n",player);
					system("pause");
					choice = Menu(partita);
					switch (choice) {
						case 1:
							if(leggereturno(partita)){
								Show_Map(leggere_mappa_gioc1(partita));}
							else
								Show_Map(leggere_mappa_gioc2(partita));
							printf("\n");
							system("pause");
							break;
						case 2:
							if(leggereturno(partita))
								ShowMapShots(leggere_mappa_gioc1(partita));
							else
								ShowMapShots(leggere_mappa_gioc2(partita));
							printf("\n");
							system("pause");
							break;
						case 3:
							if(leggereturno(partita)) {
								attacco(map_p2, &map_p1, &partita);
								if(leggere_navi2(partita)==0) {
									FinePartita(1,leggere_filename(partita));	//ELIMINARE IL FILE CORRISPONDENTE ALLA PARTITA IN GIOCO
									goto Principale;
								}
								else {
									ShowMapShots(map_p1);
								}
							}
							else {
								attacco(map_p1, &map_p2, &partita);
								if(leggere_navi1(partita)==0) {
									FinePartita(2,leggere_filename(partita));
									goto Principale;
								}
								else {
									ShowMapShots(map_p2);
								}
							}
							partita = scrivereturno(partita, !(leggereturno(partita)));
							pf = Save_Game(pf,partita);
							printf("\n");
							system("pause");
							break;
						case 0:
							printf("\n\n--------------------------------");
							printf("\nVuoi salvare la partita? (s / n)\n");
							scanf(" %c",&conferma);
							if(toupper(conferma)=='S') {
								pf = Save_Game(pf, partita);
								printf("\nPARTITA SALVATA!!!\n");
								system("pause");
							}
							goto Principale;
							break;
					}
				} while(choice!=0);
				break;
			case 2:
				// caricare una partita
				partita = Load_Game(pf, partita, filen);
				goto MenuSecondario;
				break;
			case 3:
				// regolamento 
				break;
			case 0:
				// esci 
				break;
		}
	} while(scelta<0 || scelta>3);

	system("cls");
	printf("\n\nFINE DEL PROGRAMMA\n\n"); 
	return 0;
}