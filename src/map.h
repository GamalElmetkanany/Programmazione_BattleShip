
#ifndef MAP_H_
#define MAP_H_

#define RIGHE 16
#define COLONNE 16

typedef struct {
	char matrix_board[RIGHE][COLONNE];
	char matrix_shots[RIGHE][COLONNE];
	int righe;
	int colonne;
} map;

/* MAP */
int leggere_righe(map mappa);
int leggere_colonne(map mappa);
int leggere_matrix_board(map mappa, int i, int j);
char leggere_matrix_shots(map mappa, int i, int j);
map scrivere_righe(map mappa, int righe);
map scrivere_colonne(map mappa, int colonne);
map scrivere_matrix_board(map mappa, int i, int j, int value);
map scrivere_matrix_shots(map mappa, int i, int j, char value);
//map assegna_matrix_shots();
map init_map(map);



#endif /* MAP_H_ */
