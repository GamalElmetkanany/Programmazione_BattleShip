#include "attacks.h"
#include "generics.h"
#include "ship.h"
#include "game.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * FUNZIONI PRINCIPALI
 */
void attacco(map mappaAvv, map *mappaMia, game *partita)
{
    int tipologia,scelta,x,y,tipologiamax=1,i;
    bool esito;
    skills var;


    Attacchi:
    tipologia = LeggiTipologiaAtt(*partita);

    switch(tipologia)
    {
        case 1:
            printf("\nHai scelto ATTACCO SEMPLICE\nContinuare? (SI = 1 | NO = 0): ");
            scanf("%d",&scelta);
            if (scelta==1)
            {
                LeggiXY(*mappaMia,&x,&y);
                Attacco_Semplice(mappaAvv, *&mappaMia, *&partita, x, y);
                if(leggereturno(*partita))
                    *partita = scriverecontatore1(*partita, leggerecontatore1(*partita)+1);
                else
                    *partita = scriverecontatore2(*partita, leggerecontatore2(*partita)+1);
            } 
            else {
                goto Attacchi;
            }
            break;
        case 2:
            printf("\nHai scelto ATTACCO LARGO RAGGIO\nContinuare? (SI = 1 | NO = 0): ");
            scanf("%d",&scelta);
            if (scelta==1)
            {   
                Attacco_Largo_Raggio(mappaAvv, *&mappaMia, *&partita);
                if(leggereturno(*partita)) {
                    var = leggerevariante1(*partita); 
                    var = scrivere_colpo_largo_raggio(var, leggere_colpo_largo_raggio(var)-1);
                    *partita = scriverevariante1(*partita, var);
                    *partita = scriverecontatore1(*partita, leggerecontatore1(*partita)+1);
                }
                else {
                    var = leggerevariante2(*partita); 
                    var = scrivere_colpo_largo_raggio(var, leggere_colpo_largo_raggio(var)-1);
                    *partita = scriverevariante2(*partita, var);
                    *partita = scriverecontatore2(*partita, leggerecontatore2(*partita)+1);
                }
            } 
            else {
                goto Attacchi;
            }
            break;
        case 3:
            printf("\nHai scelto ATTACCO RADAR\nContinuare? (SI = 1 | NO = 0): ");
            scanf("%d",&scelta);
            if (scelta==1)
            {
                Attacco_Radar(mappaAvv, *&mappaMia, *&partita);
                if(leggereturno(*partita)) {
                    var = leggerevariante1(*partita); 
                    var = scrivere_radar(var, leggere_radar(var)-1);
                    *partita = scriverevariante1(*partita, var);
                    *partita = scriverecontatore1(*partita, leggerecontatore1(*partita)+1);
                }
                else {
                    var = leggerevariante2(*partita); 
                    var = scrivere_radar(var, leggere_radar(var)-1);
                    *partita = scriverevariante2(*partita, var);
                    *partita = scriverecontatore2(*partita, leggerecontatore2(*partita)+1);
                }
            } 
            else {
                goto Attacchi;
            }
            break;
        case 4:
            printf("\nHai scelto BOMBARDAMENTO AEREO\nContinuare? (SI = 1 | NO = 0): ");
            scanf("%d",&scelta);
            if (scelta==1)
            {   
                Attacco_Bombardamento(mappaAvv, *&mappaMia, *&partita);
                if(leggereturno(*partita)) {
                    var = leggerevariante1(*partita); 
                    var = scrivere_bombardamento_aereo(var, leggere_bombardamento_aereo(var)-1);
                    *partita = scriverevariante1(*partita, var);
                    *partita = scriverecontatore1(*partita, leggerecontatore1(*partita)+1);
                }
                else {
                    var = leggerevariante2(*partita); 
                    var = scrivere_bombardamento_aereo(var, leggere_bombardamento_aereo(var)-1);
                    *partita = scriverevariante2(*partita, var);
                    *partita = scriverecontatore2(*partita, leggerecontatore2(*partita)+1);
                }
            } 
            else {
                goto Attacchi;
            }
            break;
    }
    if(leggereturno(*partita)) {
        *partita = assegna_mappa_gioc1(*partita, *mappaMia);
    }
    else {
        *partita = assegna_mappa_gioc2(*partita, *mappaMia);
    }
}

void Attacco_Semplice(map mappaAvv, map *mappaMia, game *partita, int x, int y)
{
	int verso=0;
	bool esito=false;
	bool esito1;

    x--;
    y--;

    if(leggere_matrix_board(mappaAvv,x,y)==0)
    {
        printf("\nCoordinate %c,%d: MANCATO", NumToChar(y+1),x+1);
        *mappaMia=scrivere_matrix_shots(*mappaMia,x,y,'w');
    } 
    else {
        esito = ctrl_att(mappaAvv, x, y);

        if(esito==false) {  //SE la nave che stiamo colpendo non è circondata da altre navi
            *mappaMia = scrivere_matrix_shots(*mappaMia, x, y, 'a');  //ALLORA affondo la nave (che avrà dunque grandezza 1)
            if(leggereturno(*partita))
                *partita = scrivere_navi2(*partita, leggere_navi2(*partita)-1);
            else
                *partita = scrivere_navi1(*partita, leggere_navi1(*partita)-1);
        }
        else {
            esito1=ctrl_att2(mappaAvv, *mappaMia, x, y, &verso);

            if(esito1==false)
            {
                *mappaMia = scrivere_matrix_shots(*mappaMia, x, y, 'c');
                printf("\nCoordinate %c,%d: COLPITO", NumToChar(y+1),x+1);
            }
            else {
                aggiorna_affondi(*&mappaMia, *&partita, x, y, verso);
                printf("\nCoordinate %c,%d: COLPITO E AFFONDATO!", NumToChar(y+1),x+1);
            }
        }
    }
    system("pause");
}

void Attacco_Radar(map mappaAvv, map *mappaMia, game *partita)
{
    int i,j,x,y,riga,colonna;
    i=0;
    LeggiXY(*mappaMia,&x,&y);
    x--;
    y--;
    
    
    //INSERIRE INTERFACCIA GRAFICA PER VISUALIZZARE LE CELLE COLPITE DAL RADAR
    riga=x-1;
    while(i<3)
    {
        colonna=y-1;
        j=0;
        while(j<3)
        {   
            if(leggere_matrix_board(mappaAvv,riga,colonna)==1)
            {
                printf("\nCoordinate %c,%d: NAVE PRESENTE", NumToChar(colonna+1),riga+1);
                *mappaMia=scrivere_matrix_shots(*mappaMia,riga,colonna,'r');
            } else 
            {
                printf("\nCoordinate %c,%d: NON C'E' UNA NAVE", NumToChar(colonna+1),riga+1);
            }
            j++;
            colonna++;
        }
        i++;
        riga++;
    }
    printf("\n");
}

void Attacco_Largo_Raggio(map mappaAvv, map *mappaMia, game *partita)
{
    int i,j,riga,colonna,x,y;
    skills var;
    LeggiXY(*mappaMia,&x,&y);

    riga=x-1;
    i=0;
    while(i<3)
    {
        colonna=y-1;
        j=0;
        while(j<3)
        {
            if((riga>=0 && riga<=RIGHE) && (colonna>=1 && colonna<=COLONNE))
            {
                Attacco_Semplice(mappaAvv, *&mappaMia, *&partita, riga, colonna);
            } 
            j++;
            colonna++;
        }
        i++;
        riga++;
    }
}

void Attacco_Bombardamento(map mappaAvv, map *mappaMia, game *partita) {
    int i,riga,colonnaNum,verso;
    char colonnaAlf;
    
    do {
        printf("Scegliere il verso del bombardamento (0 = Orizzontale, 1 = Verticale): ");
        scanf("%d",&verso);
        if(verso==1) {
            do {
                printf("Indicare la colonna da bombardare: ");
                scanf("%c",&colonnaAlf);
                colonnaNum = CharToNum(toupper(colonnaAlf));
            } while(colonnaNum<1 || colonnaNum>COLONNE);
        }
        else if(verso==0) {
            do {
                printf("Indicare la riga da bombardare: ");
                scanf("%d",&riga);
            } while(riga<1 || riga>RIGHE);
        }
    } while(verso<0 || verso>1);

    if(verso==1) {
        riga = 1;
    } else {
        colonnaNum = 1;
    }

    i=0;
    while(i<RIGHE)
    {
        if(verso==1) {
            Attacco_Semplice(mappaAvv, *&mappaMia, *&partita, riga, colonnaNum);
            riga++;
        }
        else {
            Attacco_Semplice(mappaAvv, *&mappaMia, *&partita, riga, colonnaNum);
            colonnaNum++;
        }
        i++;
    }
}



/*
 * SOTTOFUNZIONI
 */
int LeggiTipologiaAtt(game partita) {
    int tipologia, contatoreturni,i;
    skills abilita;

    if(leggereturno(partita)) {
        contatoreturni = leggerecontatore1(partita);
        abilita = leggerevariante1(partita);
    }
    else {
        contatoreturni = leggerecontatore2(partita);
        abilita = leggerevariante2(partita);
    }

    Scelta:
    do {
        i = 1;
        system("cls");
        /* CONTROLLO ATTACCHI DISPONIBILI */
        printf("ATTACCHI DISPONIBILI: ---------------------------- Turno %d", contatoreturni+1);
        printf("\n - %d: Attacco semplice",i); /* SEMPRE, MAX NON ESISTE */
        i++;
        if(leggere_colpo_largo_raggio(abilita)>0) {
            printf("\n - %d: Colpo a largo raggio\t(RIMASTI %d)",i,leggere_colpo_largo_raggio(abilita)); /* SEMPRE, MAX=3 */
            i++;
        }
        if(leggere_radar(abilita)>0) {
            printf("\n - %d: Radar\t\t\t(RIMASTI %d)",i,leggere_radar(abilita)); /* SEMPRE, MAX=3 */
            i++;
        }
        if(contatoreturni>=10 && leggere_bombardamento_aereo(abilita)>0) {
            printf("\n - %d: Bombardamento aereo\t\t\t(RIMASTI %d)",i,leggere_bombardamento_aereo(abilita)); /* DOPO 10 TURNI, MAX=1 */
            i++;
        }
        printf("\nInserisci la tua scelta: ");
        scanf("%d",&tipologia);
        i--;
    } while(tipologia<1 || tipologia>i);

    if(!ctrlTipologiaDisp(abilita, &tipologia, contatoreturni))
        goto Scelta;

    return tipologia;
}

void LeggiXY(map mappa, int *x, int *y) {
    char yAlf;

    printf("\nInserire le coordinate. . .\n");
    printf("Riga: ");
    scanf("%d",&*x);
    printf("Colonna: ");
    scanf(" %c",&yAlf);
    *y = CharToNum(toupper(yAlf));
    if (leggere_matrix_shots(mappa, *x-1, *y-1)!='0') {
        clrScreen(4);
        printf("ATTENZIONE!\nHai gia' effettuato un attacco nella posizione indicata.\nPrego, inserisci le nuove coordinate:\n\n");
        system("pause");
        clrScreen(4);
        do {
        printf("\nInserire la riga e la colonna che si vuole attaccare \n");
        printf("Riga: ");
        scanf("%d",&*x);
        printf("Colonna: ");
        scanf(" %c",&yAlf);
        *y = CharToNum(toupper(yAlf));
        clrScreen(4);
        } while(leggere_matrix_shots(mappa, *x-1, *y-1)!='0');
    }
}



/*
*   CONTROLLI 
*/
int ctrlTipologiaDisp(skills abilita, int *tipologia, int contatoreturni) {
    switch(*tipologia) {
        case 2:
            if(leggere_colpo_largo_raggio(abilita)<=0) {
                if(leggere_radar(abilita)>0) {
                    *tipologia = 3;
                    return true;
                }
                else {
                    if(leggere_bombardamento_aereo(abilita)>0 && contatoreturni>=10) {
                        *tipologia = 4;
                        return true;
                    }
                    else
                        return false;
                }
            }
            break;
        case 3:
            if(leggere_radar(abilita)<=0) {
                if(leggere_bombardamento_aereo(abilita)>0) {
                    *tipologia = 4;
                    return true;
                }
                else {
                    return false;
                }
            }
            break;
    }

    return true;
}

void aggiorna_affondi(map *mappa, game *partita, int x, int y, int verso) {
    //TROVA LIMITE
    int riga=x,colonna=y,contnavi=0;
    //SINISTRO
    if(verso==0)
        colonna = y-1;
    else
        riga = x-1;
    while(leggere_matrix_shots(*mappa, riga, colonna)=='c') {
        *mappa = scrivere_matrix_shots(*mappa, riga, colonna, 'a');
        contnavi++;
        if(verso==0)
            colonna--;
        else
            riga--;
    }
    //DESTRO
    if(verso==0)
        colonna = y+1;
    else
        riga = x+1;
    while(leggere_matrix_shots(*mappa, riga, colonna)=='c') { 
        *mappa = scrivere_matrix_shots(*mappa, riga, colonna, 'a');
        contnavi++;
        if(verso==0)
            colonna++;
        else
            riga++;
    }

    *mappa = scrivere_matrix_shots(*mappa, x, y, 'a');
    contnavi++;

    if(leggereturno(*partita))
        *partita = scrivere_navi2(*partita, leggere_navi2(*partita)-contnavi);
    else
        *partita = scrivere_navi1(*partita, leggere_navi1(*partita)-contnavi);
}

bool ctrl_att(map mappa,int x,int y)
{
	bool esito=false;
	int i,j;
	int righe,colonne;

	righe=x-1;
	i=0;
	while(i<3 && esito==false)
	{
		j=0;
		colonne=y-1;
		while(j<3 && esito==false)
		{
			if((0<=righe && righe<=RIGHE-1) && (0<=colonne && colonne<=COLONNE-1))
			{
				if(!(righe==x && colonne==y))
				{
					if(leggere_matrix_board(mappa,righe,colonne) == 1)
					{
						esito=true;
					}
				}
			}
			colonne++;
			j++;
		}
		righe++;
		i++;
	}
	return esito;
}

bool ctrl_att2(map mappaAvv, map mappaMia, int x, int y, int *verso)
{
	int riga1, riga2, colonna1, colonna2;
	bool esito = true;
	position tempPos;

	riga1=x;
	riga2=x;
	colonna1=y;
	colonna2=y;

	if(leggere_matrix_board(mappaAvv, x, y+1)!=0 || leggere_matrix_board(mappaAvv, x, y-1)!=0) {  //ORIZZONTALE
        *verso = 0;
		colonna1--;
		colonna2++;
        esito = true;
        do {
            if(0<=colonna1 && colonna1<=COLONNE-1) {
                if(leggere_matrix_shots(mappaMia, x, colonna1)=='c') {
                    colonna1--;
                } 
                else {
                    if(leggere_matrix_board(mappaAvv,x,colonna1)==1){
                        esito=false;
                        break;
                    }
                }
            }
            if(0<=colonna2 && colonna2<=COLONNE-1) {
                if(leggere_matrix_shots(mappaMia, x, colonna2)=='c') {
                    colonna2++;
                } 
                else {
                    if(leggere_matrix_board(mappaAvv,x,colonna2)==1){
                        esito=false;
                        break;
                    }
                }
            }
		} while((leggere_matrix_board(mappaAvv, x, colonna1)==1 || leggere_matrix_board(mappaAvv, x, colonna2)==1) && esito==true);
	}
	else if(leggere_matrix_board(mappaAvv, x+1, y)!=0 || leggere_matrix_board(mappaAvv, x-1, y)!=0) {	//VERTICALE
        *verso = 1;
		riga1--;
		riga2++;
        esito = true;
        do {
            if(0<=riga1 && riga1<=COLONNE-1) {
                if(leggere_matrix_shots(mappaMia, riga1, y)=='c') {
                    riga1--;
                } 
                else {
                    if(leggere_matrix_board(mappaAvv, riga1, y)==1){
                        esito=false;
                        printf("prova1 = %d \t coordinate:%d,%d \t valore:%c", esito,riga1+1,y+1,leggere_matrix_shots(mappaMia, riga1, y));
                        break;
                    }
                }
            }
            if(0<=riga2 && riga2<=COLONNE-1) {
                if(leggere_matrix_shots(mappaMia, riga2, y)=='c') {
                    riga2++;
                } 
                else {
                    if(leggere_matrix_board(mappaAvv, riga2, y)==1){
                        esito=false;
                        break;
                    }
                }
            }
		} while((leggere_matrix_board(mappaAvv, riga1, y)==1 || leggere_matrix_board(mappaAvv, riga2, y)==1) && esito==true);
	}
    
	return esito;
}