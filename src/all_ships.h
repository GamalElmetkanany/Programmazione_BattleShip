
#ifndef ALL_SHIPS_H_
#define ALL_SHIPS_H_

typedef struct{
    int cont1;
    int cont2;
    int cont3;
    int cont4;
    int cont5;
} all_ships;

all_ships scrivere_cont1(all_ships, int);
all_ships scrivere_cont2(all_ships, int);
all_ships scrivere_cont3(all_ships, int);
all_ships scrivere_cont4(all_ships, int);
all_ships scrivere_cont5(all_ships, int);

int leggere_cont1(all_ships);
int leggere_cont2(all_ships);
int leggere_cont3(all_ships);
int leggere_cont4(all_ships);
int leggere_cont5(all_ships);

#endif /* ALL_SHIPS_H_ */
