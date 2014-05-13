#include "aufgabe2.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

/* IMPLEMENTIERUNG DER METHODEN AUS AUFGABE2.H BSRvS1 SS2014 *
 *                                                           *
 *              DARF NICHT GEÄNDERT WERDEN                   *
 ************************************************************/


static struct Position InitPositions[10];
static const char *Menue = "\nSie haben folgende Auswahl:\n(B)eenden - Beendet das Programm\n(P)ause   - Pausiert die Threads\n(W)eiter  - Fortsetzen (nach einer Pause)\n";
static char initChars[10]={'0','1','2','3','4','5','6','7','8','9'};
static unsigned short showFirst = 1;

void init(void){
	int y;
	int x;
	struct Position ps;
   
  
	if(feldXdim<12 || feldYdim<8){
		perror("\n\033[38;5;9mFEHLER:\tNICHT GEN\303\234GEND PLATZ AUF DEM FELD, UM 10 THREADS UNTERZUBRINGEN\033[39;49m\n");
		exit(EXIT_FAILURE);
	}
   
	/* Feld Initialisieren */
	for(y=0;y<feldYdim;y++){
		for(x=0;x<feldXdim;x++){
			Feld[y][x]=' ';
		}
	}
   
	/* StartPositionen Initialisieren */
	for(y=0; y<10; y++){
		ps.Y = y%6;
		ps.X = y;
		InitPositions[y] = ps;
	}
}
 
 
struct Position gibStartPosition(unsigned short ThreadNr){
	struct Position ps = InitPositions[ThreadNr];
   
	if(InitPositions[1].X==0){
		perror("\n\033[38;5;9mINITIALISIERUNG FEHLT\033[39;49m\n");
		exit(EXIT_FAILURE);
	}
	if(ThreadNr>9){
		perror("\n\033[38;5;9mTHREADS MIT ID>9 WERDEN NICHT UNTERST\303\234TZT\033[39;49m\n");
		exit(EXIT_FAILURE);
	}
   
	Feld[ps.Y][ps.X] = initChars[ThreadNr];
   
	return ps;
}
 
 
struct Position gibNeuePosition(struct Position altePosition){
	char tock=Feld[altePosition.Y][altePosition.X];
	struct Position newPosition;
	unsigned short newY=0;
	unsigned short newX=0;
	unsigned short newPos[5] = {1,0,0,0,0};
	int zufallszahl = 0;
	
	if(tock==' ') pthread_exit(NULL);
   
	if(((altePosition.Y-1)>=0) && (Feld[altePosition.Y-1][altePosition.X]==' '))
		newPos[1] = 1;
	if(((altePosition.X-1)>=0) && (Feld[altePosition.Y][altePosition.X-1]==' '))
		newPos[2] = 1;
	if(((altePosition.X+1)<(feldXdim)) && (Feld[altePosition.Y][altePosition.X+1]==' '))
		newPos[3] = 1;
	if(((altePosition.Y+1)<(feldYdim)) && (Feld[altePosition.Y+1][altePosition.X]==' '))
		newPos[4] = 1;
   
	usleep(1000);   
	srand(time(NULL)*rand());  
	for(zufallszahl=rand()%5; zufallszahl<10; zufallszahl++){
		if(newPos[zufallszahl%5] == 1){
			switch(zufallszahl){
				case 1: 
					newY=altePosition.Y-1;
					newX=altePosition.X;
					break;
				case 2: 
					newY=altePosition.Y;
					newX=altePosition.X-1;
					break;
				case 3: 
					newY=altePosition.Y;
					newX=altePosition.X+1;
					break;
				case 4: 
					newY=altePosition.Y+1;
					newX=altePosition.X;
					break;
				default: 
					newY=altePosition.Y;
					newX=altePosition.X;
					break;
			}
		break;
		}     
	}
 
	newPosition.Y = newY;
	newPosition.X = newX;
   
	return newPosition;
}
 
 
void anzeigen(void){
	int y;
	int x;
   
	usleep(100000);
	if(showFirst==1){
		printf("\033[2J\033[1;1H");
	}else{
		printf("\033[K\033[s\033[1;1H");
	}
	
	for(y=-1; y<=feldYdim; y++){
		for(x=-1; x<=feldXdim; x++){
			if(y==-1 && x==-1){ /* Ecke TL */
				printf("\342\224\217"); continue;}
			if(x>-1 && x<feldXdim && (y==-1 || y==feldYdim)){ /* == */
				printf("\342\224\201"); continue;}
			if(y==-1 && x==feldXdim){ /* Ecke TR */
				printf("\342\224\223\n"); continue;}
			if(!(y==-1 || y==feldYdim) && (x==-1 || x==feldXdim)){ /* || */
				printf("\342\224\203"); 
				if(x==feldXdim)printf("\n");
				continue;}
			if(y==feldYdim && x==-1){ /* Ecke BL */
				printf("\342\224\227"); continue;}
			if(y==feldYdim && x==feldXdim){ /* Ecke BR */
				printf("\342\224\233"); continue;}
			printf("%c",Feld[y][x]); /* else */
		}
	}
	
	if(showFirst==1){
		printf("\n%s\nIhre Wahl : \n\n\033[%d;13H", Menue, (feldYdim+9));
		fflush(stdout);
		showFirst=0;
	}else{
		printf("\033[u");
		if(EingabeZeichen!=0){
			if(EingabeZeichen=='b' || EingabeZeichen=='B'){
				printf("\n\n");
			}else{
				printf("Ihre Wahl : ");
				EingabeZeichen = 0;
			}
		}
	}
	printf("\033[?25h");
	fflush(stdout);
}

