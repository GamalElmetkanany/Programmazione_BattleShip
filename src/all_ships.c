
#include "all_ships.h"

all_ships scrivere_cont1(all_ships navi, int value) {
    navi.cont1 = value;
    return navi;
}

all_ships scrivere_cont2(all_ships navi, int value) {
    navi.cont2 = value;
    return navi;
}

all_ships scrivere_cont3(all_ships navi, int value) {
    navi.cont3 = value;
    return navi;
}

all_ships scrivere_cont4(all_ships navi, int value) {
    navi.cont4 = value;
    return navi;
}

all_ships scrivere_cont5(all_ships navi, int value) {
    navi.cont5 = value;
    return navi;
}

int leggere_cont1(all_ships navi) {
    return navi.cont1;
}

int leggere_cont2(all_ships navi) {
    return navi.cont2;
}

int leggere_cont3(all_ships navi) {
    return navi.cont3;
}

int leggere_cont4(all_ships navi) {
    return navi.cont4;
}

int leggere_cont5(all_ships navi) {
    return navi.cont5;
}

