#include "generics.h"
#include <stdlib.h>
#include <ctype.h>

#define LENGTH(x)  (sizeof(x) / sizeof((x)[0]))

char Alfabeto[16] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L', 'M', 'N', 'O', 'P', 'Q', 'R'};

int CharToNum(char value) {
    int i=0;

    while(i<LENGTH(Alfabeto)) {
        if(Alfabeto[i]==value)
            break;
        i++;
    }

    i++;
    return i;
}

char NumToChar(int num) {
    return Alfabeto[num-1];
}

int MenuPrincipale() {
    int scelta;
    do {
        system("cls");
        printf("\t\t\t\t\t\t\t\tBattaglia Navale 2022\n\n\n");
        printf("1.  Nuova Partita \n");
        printf("2.  Continua Partita \n");
        printf("3.  Regole di gioca \n\n");
        printf("0.  Fine \n\n\n\n");
        printf("\t\t\t\t\t\t\t\t      SCELTA:\n\t\t\t\t\t\t\t\t\t");
        fflush(stdin);
        scanf("%d",&scelta);
    } while(scelta<0 || scelta>3);

    return scelta;
}

int Menu(game partita) {
    int scelta, player;
    if(leggereturno(partita))
        player = 1;
    else
        player = 2;
    do {
        system("cls");
        printf("\t\t\t\t\t\t\t\tBattaglia Navale 2022\n\n\n\n\n");
        printf("Nuova Partita\n\n");
        printf("1. Visualizza la disposizione delle navi\n");
        printf("2. Visualizza il riepilogo degli attacchi\n\n\n");
        printf("-------------- Giocatore %d\n",player);
        printf("3 - Procedi con un attacco\n\n\n");
        printf("0. Torna al Menu' Principale\n");
        printf("\nEffettua una scelta -> ");
        fflush(stdin);
        scanf("%d", &scelta);
    } while (scelta < 0 || scelta > 3);

    return scelta;
}

bool LeggereNave5(bool load,game partita,FILE *pf)
{
    char c;
    int num,count;

    pf=fopen(leggere_filename(partita),"r");
    
    count=0;
    c=fgetc(pf);
    while(c != EOF)
    {
        printf("count=%d",count);
        system("pause");
        if(count == 0 || count == 9)
        {
            while(c != '\n')
            {
                if(c == '|'){
                num++;
                printf("%c",c);
                system("pause");
                }
            }
            count++;
        } else if(count != 1 || count != 9)
            {count++;}

        c=fgetc(pf);
    }
    

    fclose(pf);

    printf("num=%d",num);
    system("pause");

    if(num == 70)
    load=true;
    else 
    load=false;
    
    return load;
}

game Carica_Navi(game partita, FILE *pf, bool player, int size, int i, int n) {
    map mappa;
    ship nave;

    if(player)
        mappa = leggere_mappa_gioc1(partita);
    else
        mappa = leggere_mappa_gioc2(partita);

    nave = scrivere_size(nave, size);
    
    do {
        while(i<n) {
            partita = Insert_Nave(&nave, &mappa, i, partita, pf);
            i++;
            Show_Map(mappa);
            system("pause");
        }
        i = 0;
        nave = scrivere_size(nave, leggere_size(nave)+1);
        size++;
        n--;
    } while(n>0);

    if(player)
        partita = scrivere_mappa_gioc1(partita, mappa);
    else
        partita = scrivere_mappa_gioc2(partita, mappa);
    
    return partita;
}

game Insert_Nave(ship *nave, map *mappa, int i, game partita, FILE *pf) {
    int numvolte, verso, riga, colonnaNum;
    bool esito, spazio;
    char colonnaAlf;

    system("cls");
    printf("POSIZIONAMENTO NAVI (Grandezza: %d celle)\n", leggere_size(*nave));
    printf("----------------------------------------\n");
    printf("Nave %d:\n\n", i+1);
    do {
        do {
            clrScreen(4);
            printf("In quale riga? ");
            fflush(stdin);
            scanf("%d",&riga);
            printf("\nIn quale colonna? ");
            fflush(stdin);
            scanf(" %c",&colonnaAlf);
            colonnaNum = CharToNum(toupper(colonnaAlf));

            riga--;
            colonnaNum--;
            if(leggere_size(*nave)>1) {
                do {
                    printf("\nDecidere il verso: (0 = orizzontale | 1 = verticale) ");
                    fflush(stdin);
                    scanf("%d",&verso);
                } while(verso<0 || verso>1);
            }
            spazio = ctrlSpace(riga, colonnaNum, verso, leggere_size(*nave));
        } while((riga<0 || riga>(RIGHE-1)) || (colonnaNum<0 || colonnaNum>(COLONNE-1)) || spazio==false);

        *nave = fill_nave(*&nave, riga, colonnaNum, verso);
        esito = ctrl_Pos(*mappa, *nave, riga, colonnaNum);
    } while(!esito);

    numvolte = 0;
    while(numvolte<leggere_size(*nave)) {
        if(leggere_size(*nave)==1) {
            *mappa = scrivere_matrix_board(*mappa, riga, colonnaNum, 1);
        }
        else {
            switch(leggere_verso(*nave)) {
                case 0:
                    *mappa = scrivere_matrix_board(*mappa, riga, colonnaNum+numvolte, 1);
                    break;
                case 1:
                    *mappa = scrivere_matrix_board(*mappa, riga+numvolte, colonnaNum, 1);
                    break;
            }
        }
        numvolte++;
    }

    partita = AggiornaContNavi(partita, numvolte);
    pf = Save_Game_Ship(pf, partita, mappa);

    return partita;
}

game AggiornaContNavi(game partita, int numvolte) {
    all_ships allships;

    if(leggereturno(partita))
        allships = leggere_all_ships1(partita);
    else
        allships = leggere_all_ships2(partita);

    switch(numvolte) {
        case 1:
            allships = scrivere_cont1(allships, leggere_cont1(allships)+1);
            break;
        case 2:
            allships = scrivere_cont2(allships, leggere_cont2(allships)+1);
            break;
        case 3:
            allships = scrivere_cont3(allships, leggere_cont3(allships)+1);
            break;
        case 4:
            allships = scrivere_cont4(allships, leggere_cont4(allships)+1);
            break;
        case 5:
            allships = scrivere_cont5(allships, leggere_cont5(allships)+1);
            break;
    }
    
    if(leggereturno(partita))
        partita = scrivere_all_ships1(partita, allships);
    else
        partita = scrivere_all_ships2(partita, allships);

    return partita;
}

bool ctrlSpace(int riga, int colonna, int verso, int size) {
    int i;
    bool spazio=true;

    i=0;
    while(i<size && spazio==true) {
        switch(verso) {
            case 0:
                if(!(0<=riga && riga<=RIGHE-1 && 0<=colonna+i && colonna+i<=COLONNE-1))
                    spazio=false;
                break;
            case 1:
                if(!(0<=riga+i && riga+i<=RIGHE-1 && 0<=colonna && colonna<=COLONNE-1))
                    spazio=false;
                break;
        }
        i++;
    }
    if(!spazio) {
        clrScreen(4);
        printf("ATTENZIONE!\nLo spazio per posizionare la nave nelle coordinate indicate e' insufficiente\nPrego, inserisci le nuove coordinate.\n\n");
        system("pause");
        clrScreen(4);
    }

    return spazio;
}

void clrScreen(int i) {
    printf("%c[f", ASCII_ESC);
    printf( "%c[%dB", ASCII_ESC, i);
    printf("%c[0J", ASCII_ESC);
}

bool ctrl_Pos(map mappa, ship nave, int x, int y) {
    int k=0, i, j, riga, colonna;
    bool esito = true;

    int flag=1;

    while(k<leggere_size(nave)) {
        if(leggere_verso(nave)==0)
            riga = x-1;
        else
            riga = x-1+k;
        i = 0;
        while(i<3 && flag) {
            if(leggere_verso(nave)==0)
                colonna = y-1+k;
            else
                colonna = y-1;
            j = 0;
            while(j<3 && flag) {
                if(0<=riga && riga<=RIGHE-1 && 0<=colonna && colonna<=COLONNE-1) {
                    if(leggere_matrix_board(mappa, riga, colonna) != 0) {
                        flag=0;
                        clrScreen(4);
                    }
                }
                colonna++;
                j++;
            }
            riga++;
            i++;
        }
        k++;
    }
    if (flag == 0){
        clrScreen(4);
        printf("ATTENZIONE!\nLa posizione indicata non e' disponibile!\nPrego, inserire le nuove coordinate.\n\n");
        system("pause");
        esito = false;
    }
    

    return esito;
}

map Init_Map(map mappa) {
    mappa = scrivere_righe(mappa, RIGHE);
    mappa = scrivere_colonne(mappa, COLONNE);

    int i = 0;
    while(i < leggere_righe(mappa)) {
        int j = 0;
        while(j < leggere_colonne(mappa)) {
            mappa = scrivere_matrix_board(mappa, i, j, 0);
            mappa = scrivere_matrix_shots(mappa, i, j, '0');
            j++;
        }
        i++;
    }

    return mappa;
}

void Show_Map(map mappa) {
    system("cls");
    int j=0;

    printf("    |");
    while(j<RIGHE)
    {
        printf(" %c  |",Alfabeto[j]);
        j++;
    }

    int i = 0;
    int k=1;
    while(k<=COLONNE)
    {
        if(k<=9)
        {
        printf("\n");
        printf("%d   |",k);
        j=0;
            while(j < leggere_righe(mappa)) {

                    printf(" %d  |", leggere_matrix_board(mappa, i, j));
                    j++;
            }
            i++;
            k++;
        }else if(k>=10)
            {   printf("\n");
                printf("%d  |",k);
                j=0;
                while(j < leggere_righe(mappa)) {

                    printf(" %d  |", leggere_matrix_board(mappa, i, j));
                    j++;
                }
                i++;
                k++;
            }
    } printf("\n");
}

void ShowMapShots(map mappa)
{
    system("cls");
    int j=0;

    printf("    |");
    while(j<RIGHE)
    {
        printf(" %c  |",Alfabeto[j]);
        j++;
    }

    int i = 0;
    int k=1;
    while(k<=COLONNE)
    {
        if(k<=9)
        {
        printf("\n");
        printf("%d   |",k);
        j=0;
            while(j < leggere_righe(mappa)) {

                    printf(" %c  |", leggere_matrix_shots(mappa, i, j));
                    j++;
            }
            i++;
            k++;
        }else if(k>=10)
            {   printf("\n");
                printf("%d  |",k);
                j=0;
                while(j < leggere_righe(mappa)) {

                    printf(" %c  |", leggere_matrix_shots(mappa, i, j));
                    j++;
                }
                i++;
                k++;
            }
    } printf("\n");
}

void FinePartita(int player, const char* filename) {
    system("cls");
    printf("\t\t\t\t\t\t\t\tBattaglia Navale 2022\n\n\n");
    printf("Complimenti!\n");
    printf("Il giocatore %d vince la partita\n", player);
    system("pause");
    remove(filename);
}