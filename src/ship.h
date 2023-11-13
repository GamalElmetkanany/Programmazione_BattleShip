
#ifndef SHIP_H_
#define SHIP_H_

typedef struct {
	int riga;
	int colonna;
} position;

typedef struct {
	int size;
	position posizioni[5];
	int verso;
} ship;

ship fill_nave(ship *nave, int riga, int colonna, int verso);
ship scrivere_size(ship, int);
int leggere_size(ship);
ship scrivere_verso(ship, int);
int leggere_verso(ship);

ship scrivere_posizione(ship nave, position pos, int i);
position leggere_posizione(ship, int);

position scrivere_riga(position, int);
position scrivere_colonna(position, int);
int leggere_riga(position);
int leggere_colonna(position);

#endif /* SHIP_H_ */
