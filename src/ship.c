
#include "ship.h"
#include <stdio.h>

ship scrivere_posizione(ship nave, position pos, int i) {
    nave.posizioni[i] = pos;
    return nave;
}

position leggere_posizione(ship nave, int i) {
    return nave.posizioni[i];
}

ship fill_nave(ship *nave, int riga, int colonna, int verso) {
    int i = 0;

    position pos;
    pos = scrivere_riga(pos, riga);
    pos = scrivere_colonna(pos, colonna);

    *nave = scrivere_posizione(*nave, pos, 0);
    *nave = scrivere_verso(*nave, verso);

    while(i < leggere_size(*nave)) {
        *nave = scrivere_posizione(*nave, pos, i);
        pos = scrivere_riga(pos, leggere_riga(pos)+1);
        pos = scrivere_colonna(pos, leggere_colonna(pos)+1);
        i++;
    }

    ship nav = *nave;
    return nav;
}

ship scrivere_size(ship nave, int size) {
	nave.size = size;
	return nave;
}

int leggere_size(ship nave) {
    return nave.size;
}

ship scrivere_verso(ship nave, int verso) {
	nave.verso = verso;
	return nave;
}

int leggere_verso(ship nave) {
    return nave.verso;
}

position scrivere_riga(position posizione,int riga)
{
    posizione.riga = riga;
    return posizione;
}

int leggere_riga(position posizione)
{
	return posizione.riga;
}

position scrivere_colonna(position posizione,int colonna)
{
    posizione.colonna = colonna;
    return posizione;
}

int leggere_colonna(position posizione)
{
	return posizione.colonna;
}

