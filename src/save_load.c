#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "save_load.h"
#include "generics.h"

//SISTEMARE IL TURNO NEL CASO DEL LOAD GAME SHIP 
//SISTEMARE A CAPO DEL COLPITO E MANCATO
//SISTEMARE IL CARICAMENTE CHE MI RIPORTA SEMPRE NEL LOAD GAME SHIP ( posso sistemare con leggere | , se sono 35 o meno in 1 e 4 riga del file )


FILE* Save_Game_Ship(FILE *pf, game partita,map *mappa)
{
    int i,j,temp1,temp2,temp3,temp4,temp5;

    if (leggereturno(partita)) {
        pf = fopen(leggere_filename(partita),"w");

        if(pf!=NULL) {

            //GIOCATORE 1 ----------------------------------------------------------------------------------------------------
            //NUMERO ALL_SHIPS
            temp1=leggere_cont1(leggere_all_ships1(partita));
            temp2=leggere_cont2(leggere_all_ships1(partita));
            temp3=leggere_cont3(leggere_all_ships1(partita));
            temp4=leggere_cont4(leggere_all_ships1(partita));
            temp5=leggere_cont5(leggere_all_ships1(partita));
            fprintf(pf,"%d,%d,%d,%d,%d",temp1,temp2,temp3,temp4,temp5);
            fprintf(pf,"\n");

            //COORDINATE NAVI SU MATRIX_BOARD --------------------------------------------------------------------------------
            i=0;
            while(i<RIGHE)
            {
                j=0;
                while(j<COLONNE)
                {
                    if(leggere_matrix_board(*mappa,i,j)==1)
                    {
                        fprintf(pf,"%d,%d|",i+1,j+1);
                    }
                    j++;
                }
                i++;
            }
            fclose(pf);
        }
        else 
            printf("ERRORE DI APERTURA DEL FILE ! ");
    }
    else {
        int count=0;
        char c;
        FILE *fp;

        fp = fopen("temp.txt","w");
        pf = fopen(leggere_filename(partita),"r");
        c = fgetc(pf);
        while(c != EOF) {
            if(c=='\n')
                count++;
            if(count<2) {
                fputc(c, fp);
            }
            c = fgetc(pf);
        } 
        fprintf(fp,"\n");
        fclose(pf);
        fclose(fp);
        

        fp = fopen("temp.txt","r");
        pf = fopen(leggere_filename(partita),"w");
        c = fgetc(fp);
        while(c != EOF) {
            fputc(c, pf);
            c = fgetc(fp);
        }
        fclose(fp);
        remove("temp.txt");

        if(pf!=NULL)
        {
            //GIOCATORE 2 ----------------------------------------------------------------------------------------------------
            //NUMERO ALL_SHIPS
            temp1=leggere_cont1(leggere_all_ships2(partita));
            temp2=leggere_cont2(leggere_all_ships2(partita));
            temp3=leggere_cont3(leggere_all_ships2(partita));
            temp4=leggere_cont4(leggere_all_ships2(partita));
            temp5=leggere_cont5(leggere_all_ships2(partita));
            fprintf(pf,"%d,%d,%d,%d,%d",temp1,temp2,temp3,temp4,temp5);
            fprintf(pf,"\n");
            
            //COORDINATE NAVI SU MATRIX_BOARD ---------------------------------------------------
            i=0;
            while(i<RIGHE)
            {
                j=0;
                while(j<COLONNE)
                {
                    if(leggere_matrix_board(*mappa,i,j)==1)
                        fprintf(pf,"%d,%d|",i+1,j+1);
                    j++;
                }
                i++;
            }
            fprintf(pf,"\n");
            fclose(pf);
        }
        else 
            printf("ERRORE DI APERTURA DEL FILE ! ");
    }
    return pf;
}

FILE* Save_Game(FILE *pf, game partita)
{
    pf = fopen(leggere_filename(partita),"w");
	int i,j;
	int temp1,temp2,temp3;


	if(pf!=NULL)
	{   
        //GIOCATORE 1 ----------------------------------------------------------------------------------------------------
        //COORDINATE NAVI SU MATRIX_BOARD ---------------------------------------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_board(leggere_mappa_gioc1(partita),i,j)==1)
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");
        //-----------------------------------------------------------------------------------
        
        
        //COORDINATE NAVI SU MATRIX_SHOTS ---------------------------------------------------
        //AFFONDATO ---------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc1(partita),i,j) == 'a')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");

        //COLPITO -----------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc1(partita),i,j) == 'c')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");

        //RADAR -------------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc1(partita),i,j) == 'r')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");

        //ACQUA -------------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc1(partita),i,j) == 'w')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");
        //-----------------------------------------------------------------------------------

        //VARIANTI

        //BOMBARDAMENTO,COLPO LARGO RAGGIO,RADAR
        temp1=leggere_bombardamento_aereo(leggerevariante1(partita));
        temp2=leggere_colpo_largo_raggio(leggerevariante1(partita));
        temp3=leggere_radar(leggerevariante1(partita));
        fprintf(pf,"%d,%d,%d",temp1,temp2,temp3);
        fprintf(pf,"\n");

        //CONTATORE NAVI
        temp1=leggere_navi2(partita);
        fprintf(pf,"%d",temp1);
        fprintf(pf,"\n");

        //CONTATORE TURNO PLAYER1
        temp1=leggerecontatore1(partita);
        fprintf(pf,"%d",temp1);
        fprintf(pf,"\n");

        //TURNO GIOCO ( 1 = player1 / 0 = player2 )
        if(leggereturno(partita)==1)
        	fprintf(pf,"%d",1);
        else
        	fprintf(pf,"%d",0);
        fprintf(pf,"\n");        
        
        //GIOCATORE 2 ----------------------------------------------------------------------------------------------------

        //COORDINATE NAVI SU MATRIX_BOARD ---------------------------------------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_board(leggere_mappa_gioc2(partita),i,j)==1)
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");
        //-----------------------------------------------------------------------------------
        
        
        //COORDINATE NAVI SU MATRIX_SHOTS ---------------------------------------------------
        //AFFONDATO ---------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc2(partita),i,j) == 'a')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");

        //COLPITO -----------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc2(partita),i,j) == 'c')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");

        //RADAR -------------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc2(partita),i,j) == 'r')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");

        //ACQUA -------------------------
        i=0;
        while(i<16)
        {
            j=0;
            while(j<16)
            {
                if(leggere_matrix_shots(leggere_mappa_gioc2(partita),i,j) == 'w')
                {
                    fprintf(pf,"%d,%d|",i+1,j+1);
                }
                j++;
            }
            i++;
        }
        fprintf(pf,"\n");
        //-----------------------------------------------------------------------------------

        //VARIANTI

        //BOMBARDAMENTO,COLPO LARGO RAGGIO,RADAR ----------------------------------------- PLAYER 2
        temp1=leggere_bombardamento_aereo(leggerevariante2(partita));
        temp2=leggere_colpo_largo_raggio(leggerevariante2(partita));
        temp3=leggere_radar(leggerevariante2(partita));
        fprintf(pf,"%d,%d,%d",temp1,temp2,temp3);
        fprintf(pf,"\n");

        //CONTATORE NAVI ----------------------------------------- PLAYER 2
        temp1=leggere_navi1(partita);
        fprintf(pf,"%d",temp1);
        fprintf(pf,"\n");

        //CONTATORE TURNO ----------------------------------------- PLAYER 2
        temp1=leggerecontatore2(partita);
        fprintf(pf,"%d",temp1);
        fprintf(pf,"\n");
    } 
    else
    {
    	printf("ERRORE DI APERTURA DEL FILE ! ");
    }

	fclose(pf);
	return pf;
}

game Load_Game_Ship(FILE *pf, game partita)
{
    if(pf != NULL) {
        int *x, *y, count=0, length=0, i, j;
        char line[256];
        bool coordinata;

        while (fgets(line, sizeof line, pf) != NULL) //read a line
        {
            x = (int*)malloc(length * sizeof(int));
            y = (int*)malloc(length * sizeof(int));
            i = 0;
            j = 0;

            if(count == 0) {
                partita = CaricaAllShips(partita, line, true);
            }
            else if(count == 2) {
                partita = CaricaAllShips(partita, line, false);
            }
            else if(count == 1 || count == 3) {
                coordinata = true;
                char *end_string;
                char *string = strtok_s(line, "|", &end_string);
                while(string != NULL)
                {
                    char *end_num;
                    char *num = strtok_s(string, ",", &end_num);
                    while(num != NULL) {
                        if(coordinata) {
                            i++;
                            x = realloc(x, i * sizeof(int));
                            x[i-1] = atoi(num);
                        }
                        else {
                            j++;
                            y = realloc(y, j * sizeof(int));
                            y[j-1] = atoi(num);
                        }
                        coordinata = !coordinata;
                        num = strtok_s(NULL, ",", &end_num);
                    }
                    string = strtok_s(NULL, "|", &end_string);
                }
                if(count==1)
                    partita = CaricaMatrixBoard(partita, x, y, j, true);
                else
                    partita = CaricaMatrixBoard(partita, x, y, j, false);
            }
            count++;
        }
        partita = CaricaNavi_Load(partita, pf);
    }
    else
    {
        //file doesn't exist
        printf("IL FILE NON ESISTE");
    }


    return partita;
}

game CaricaNavi_Load(game partita, FILE* pf) {
    if(leggere_cont1(leggere_all_ships1(partita)) == 5) {
        if(leggere_cont2(leggere_all_ships1(partita)) == 4) {
            if(leggere_cont3(leggere_all_ships1(partita)) == 3) {
                if(leggere_cont4(leggere_all_ships1(partita)) == 2) {
                    if(leggere_cont5(leggere_all_ships1(partita)) < 1) {
                        partita = Carica_Navi(partita, pf, true, 5, 0, 1);
                    }
                }
                else {
                    partita = Carica_Navi(partita, pf, true, 4, leggere_cont4(leggere_all_ships1(partita)), 2);
                }
            }
            else {
                partita = Carica_Navi(partita, pf, true, 3, leggere_cont3(leggere_all_ships1(partita)), 3);
            }
        }
        else {
            partita = Carica_Navi(partita, pf, true, 2, leggere_cont2(leggere_all_ships1(partita)), 4);
        }
    }
    else {
        partita = Carica_Navi(partita, pf, true, 1, leggere_cont1(leggere_all_ships1(partita)), 5);
    }    
    
    system("cls");
    printf("Turno del Giocatore 2\n---------------------\n");
    system("pause");

    partita = scrivereturno(partita, !(leggereturno(partita)));

    if(leggere_cont1(leggere_all_ships2(partita)) == 5) {
        if(leggere_cont2(leggere_all_ships2(partita)) == 4) {
            if(leggere_cont3(leggere_all_ships2(partita)) == 3) {
                if(leggere_cont4(leggere_all_ships2(partita)) == 2) {
                    if(leggere_cont5(leggere_all_ships2(partita)) < 1) {
                        partita = Carica_Navi(partita, pf, false, 5, 0, 1);
                    }
                }
                else {
                    partita = Carica_Navi(partita, pf, false, 4, leggere_cont4(leggere_all_ships2(partita)), 2);
                }
            }
            else {
                partita = Carica_Navi(partita, pf, false, 3, leggere_cont3(leggere_all_ships2(partita)), 3);
            }
        }
        else {
            partita = Carica_Navi(partita, pf, false, 2, leggere_cont2(leggere_all_ships2(partita)), 4);
        }
    }
    else {
        partita = Carica_Navi(partita, pf, false, 1, leggere_cont1(leggere_all_ships2(partita)), 5);
    }
    
    partita = scrivereturno(partita, !(leggereturno(partita)));

    return partita;
}

game Load_Game(FILE *pf, game partita, char filename[128])
{
    int *x, *y, length, count=0, i,j;
    bool coordinata , load;

    printf("Indicare il nome di una partita precedentemente salvata:\n");
    scanf("%123s",filename);
    strcat(filename,".txt");
    partita = scrivere_filename(partita, filename);
    pf = fopen(leggere_filename(partita),"r");
    partita = Init_All(partita, false);

    load=LeggereNave5(load,partita,pf);
    printf("%d",load);
    system("pause");
    //SISTEMARE LEGGE CONT 0 0 
    if(load)
    {
        printf("entra qua");
        system("pause");
        // Assegno grandezza ai vettori dinamici
        length = 0; // variabile che tiene conto della lunghezza in cambiamento dei vettori
        x = (int*)malloc(length * sizeof(int));
        y = (int*)malloc(length * sizeof(int));

        if (pf != NULL)
        {
            char line[256];
            while (fgets(line, sizeof line, pf) != NULL) //read a line
            {
                x = (int*)malloc(length * sizeof(int));
                y = (int*)malloc(length * sizeof(int));
                i = 0;
                j = 0;
                coordinata = true;
                if (count == 0 || count == 9) //NAVI PRESENTI ---------------------------------------------------------------
                {
                    char *end_string;
                    char *string = strtok_s(line, "|", &end_string);
                    while(string != NULL)
                    {
                        char *end_num;
                        char *num = strtok_s(string, ",", &end_num);
                        while(num != NULL) {
                            if(coordinata) {
                                i++;
                                x = realloc(x, i * sizeof(int));
                                x[i-1] = atoi(num);
                            }
                            else {
                                j++;
                                y = realloc(y, j * sizeof(int));
                                y[j-1] = atoi(num);
                            }
                            coordinata = !coordinata;
                            num = strtok_s(NULL, ",", &end_num);
                        }
                        string = strtok_s(NULL, "|", &end_string);
                    }
                    if(count==0)
                        partita = CaricaMatrixBoard(partita, x, y, j, true);
                    else
                        partita = CaricaMatrixBoard(partita, x, y, j, false);
                }
                else if (count == 1 || count == 10) //NAVI AFFONDATE ------------------------------------------------------------------
                {
                    char *end_string;
                    char *string = strtok_s(line, "|", &end_string);
                    while(string != NULL)
                    {
                        char *end_num;
                        char *num = strtok_s(string, ",", &end_num);
                        while(num != NULL) {
                            if(coordinata) {
                                i++;
                                x = realloc(x, i * sizeof(int));
                                x[i-1] = atoi(num);
                            }
                            else {
                                j++;
                                y = realloc(y, j * sizeof(int));
                                y[j-1] = atoi(num);
                            }
                            coordinata = !coordinata;
                            num = strtok_s(NULL, ",", &end_num);
                        }
                        string = strtok_s(NULL, "|", &end_string);
                    }
                
                    if(count == 1)
                        partita = CaricaMatrixShots(partita, x, y, j, 'a', true);
                    else
                        partita = CaricaMatrixShots(partita, x, y, j, 'a', false);
                }
                else if (count == 2 || count == 11) //NAVI COLPITE ---------------------------------------------------------------
                {
                    char *end_string;
                    char *string = strtok_s(line, "|", &end_string);
                    while(string != NULL)
                    {
                        char *end_num;
                        char *num = strtok_s(string, ",", &end_num);
                        while(num != NULL) {
                            if(coordinata) {
                                i++;
                                x = realloc(x, i * sizeof(int));
                                x[i-1] = atoi(num);
                            }
                            else {
                                j++;
                                y = realloc(y, j * sizeof(int));
                                y[j-1] = atoi(num);
                            }
                            coordinata = !coordinata;
                            num = strtok_s(NULL, ",", &end_num);
                        }
                        string = strtok_s(NULL, "|", &end_string);
                    }
                
                    if(count == 1)
                        partita = CaricaMatrixShots(partita, x, y, j, 'c', true);
                    else
                        partita = CaricaMatrixShots(partita, x, y, j, 'c', false);
                }
                else if (count == 3 || count == 12) //NAVI RADAR ---------------------------------------------------------------
                {
                    char *end_string;
                    char *string = strtok_s(line, "|", &end_string);
                    while(string != NULL)
                    {
                        char *end_num;
                        char *num = strtok_s(string, ",", &end_num);
                        while(num != NULL) {
                            if(coordinata) {
                                i++;
                                x = realloc(x, i * sizeof(int));
                                x[i-1] = atoi(num);
                            }
                            else {
                                j++;
                                y = realloc(y, j * sizeof(int));
                                y[j-1] = atoi(num);
                            }
                            coordinata = !coordinata;
                            num = strtok_s(NULL, ",", &end_num);
                        }
                        string = strtok_s(NULL, "|", &end_string);
                    }
                
                    if(count == 1)
                        partita = CaricaMatrixShots(partita, x, y, j, 'r', true);
                    else
                        partita = CaricaMatrixShots(partita, x, y, j, 'r', false);
                }
                else if (count == 4 || count == 13) //NAVI ACQUA ---------------------------------------------------------------
                {
                    char *end_string;
                    char *string = strtok_s(line, "|", &end_string);
                    while(string != NULL)
                    {
                        char *end_num;
                        char *num = strtok_s(string, ",", &end_num);
                        while(num != NULL) {
                            if(coordinata) {
                                i++;
                                x = realloc(x, i * sizeof(int));
                                x[i-1] = atoi(num);
                            }
                            else {
                                j++;
                                y = realloc(y, j * sizeof(int));
                                y[j-1] = atoi(num);
                            }
                            coordinata = !coordinata;
                            num = strtok_s(NULL, ",", &end_num);
                        }
                        string = strtok_s(NULL, "|", &end_string);
                    }

                    if(count == 1)
                        partita = CaricaMatrixShots(partita, x, y, j, 'w', true);
                    else
                        partita = CaricaMatrixShots(partita, x, y, j, 'w', false);
                }
                else if(count == 5 || count == 14) //CARICARE VARIANTI
                {   
                    int c, x;
                    char *end_string;
                    skills varianti;

                    char *string = strtok_s(line, "|", &end_string);
                    while(string != NULL)
                    {
                        c=1;
                        char *end_num;
                        char *num = strtok_s(string, ",", &end_num);
                        while(num != NULL) {
                            if(c==1) //BOMBARDAMENTO
                                varianti = scrivere_bombardamento_aereo(varianti, atoi(num));
                            else if(c==2) //COLPO LARGO RAGGIO
                                varianti = scrivere_colpo_largo_raggio(varianti, atoi(num));
                            else if(c==3) //RADAR
                                varianti = scrivere_radar(varianti, atoi(num));
                            c++;
                            num = strtok_s(NULL, ",", &end_num);
                        }
                        string = strtok_s(NULL, "|", &end_string);
                    }

                    if(count == 5)
                        partita = CaricaAbilita(partita, varianti, true);
                    else
                        partita = CaricaAbilita(partita, varianti, true);
                }
                else if(count == 6 || count == 15) //CONTATORE NAVI
                {
                    int x;
                    char *end_string;
                    char *string = strtok_s(line, "", &end_string);
                    while(string != NULL) {
                        x = atoi(string);
                        string = strtok_s(NULL, "", &end_string);
                    }

                    if(count == 6)
                        partita = CaricaContNavi(partita,x,true);
                    else
                        partita = CaricaContNavi(partita,x,false);
                }
                else if(count == 7 || count == 16) //CONTATORE TURNI DEL SINGOLO GIOCATORE
                {
                    int x;
                    char *end_string;
                    char *string = strtok_s(line, "", &end_string);
                    while(string != NULL) {
                        x = atoi(string);
                        string = strtok_s(NULL, "", &end_string);
                    }

                    if(count == 7)
                        partita=CaricaContTurni(partita,x,true);
                    else
                        partita=CaricaContTurni(partita,x,false);
                }
                else if(count == 8) {
                    bool turno;
                    char *end_string;
                    char *string = strtok_s(line, "", &end_string);
                    while(string != NULL) {
                        if(string[0]=='1')
                            turno = true;
                        else if(string[0]=='0')
                            turno = false;
                        string = strtok_s(NULL, "", &end_string);
                    }
                    partita = scrivereturno(partita, turno);
                }
                count++;
            }
            fclose(pf);
        }
        else
        {
            //file doesn't exist
            printf("IL FILE NON ESISTE");
        }
    }
    else {
        printf("entra qua1");
        system("pause");
        printf("%d %d",leggere_cont5(leggere_all_ships1(partita)) ,leggere_cont5(leggere_all_ships2(partita) ));
        system("pause");
        partita = Load_Game_Ship(pf, partita);
    }

    return partita;
}

game CaricaAllShips(game partita, char line[256], bool player) 
{
    int c, x;
    char *end_num;
    all_ships allships;

    c=1;
    char *num = strtok_s(line, ",", &end_num);
    while(num != NULL) 
    {
        if(c==1) //DIMENSIONE 1
        {
            allships = scrivere_cont1(allships, atoi(num));
        }
        else if(c==2) //DIMENSIONE 2
        { 
            allships = scrivere_cont2(allships, atoi(num));
        }
        else if(c==3) //DIMENSIONE 3
        {
            allships = scrivere_cont3(allships, atoi(num));
        }
        else if(c==4) //DIMENSIONE 4
        {
            allships = scrivere_cont4(allships, atoi(num));
        }
        else if(c==5) //DIMENSIONE 5
        { 
            allships = scrivere_cont5(allships, atoi(num));
        }
        c++;
        num = strtok_s(NULL, ",", &end_num);
    }

    if(player)
        partita = scrivere_all_ships1(partita, allships);
    else
        partita = scrivere_all_ships2(partita, allships);

    return partita;
}

game CaricaMatrixBoard(game partita, int* x, int* y, int length, bool player) {
    int i,j;
    map mappa;

    if(player)
        mappa = leggere_mappa_gioc1(partita);
    else
        mappa = leggere_mappa_gioc2(partita);

    i = 0;
    while(i < length) {
        mappa = scrivere_matrix_board(mappa, x[i]-1, y[i]-1, 1);
        i++;
    }
    
    if(player)
        partita = scrivere_mappa_gioc1(partita, mappa);
    else
        partita = scrivere_mappa_gioc2(partita, mappa);
    return partita;
}

game CaricaMatrixShots(game partita, int* x, int* y, int length, char value, bool player) {
    int i,j;
    map mappa;

    if(player)
        mappa = leggere_mappa_gioc1(partita);
    else
        mappa = leggere_mappa_gioc2(partita);
    
    i = 0;
    while(i < length) { // in pseudo NON mettere il -1
        mappa = scrivere_matrix_shots(mappa, x[i]-1, y[i]-1, value);
        i++;
    }

    if(player)
        partita = scrivere_mappa_gioc1(partita, mappa);
    else
        partita = scrivere_mappa_gioc2(partita, mappa);
    return partita;
}

game CaricaAbilita(game partita, skills varianti, bool player)
{
	skills abilita;

	if(player)
		partita = scriverevariante1(partita, varianti);
	else
		partita = scriverevariante2(partita, varianti);

	return partita;
}

game CaricaContNavi(game partita, int cont, bool player)
{
	if(player)
		partita = scrivere_navi1(partita, cont);
	else
		partita = scrivere_navi2(partita, cont);

	return partita;
}

game CaricaContTurni(game partita, int cont, bool player)
{
    if(player)
		partita = scriverecontatore1(partita, cont);
	else
		partita = scriverecontatore2(partita, cont);

	return partita;
}