#ifndef AUFGABE2_H
#define AUFGABE2_H


/* HEADERDATEI ZUM LÖSEN DER AUFGABE2 DER VORLESUNG BSRvS1 SS2014 *
 *                                                                *
 *                    DARF NICHT GEÄNDERT WERDEN                  *
 *****************************************************************/
 
#define feldXdim 14
#define feldYdim  8 


/*    Deklarationen globaler Elemente    *
******************************************/  

/* Feld: 
*  Zeichen-Array zur Darstellung der Threadpositionen auf dem Bildschirm.
*  Dimensionen des Feldes sind durch feldYdim und feldXdim festgelegt.
*  Dient als anschaulicher, gemeinsamer Speicher für die Threads.
*  Angezeigte Zeichen '0'-'9' entsprechen den Daten der jeweiligen Threads.
*/  
  char Feld[feldYdim][feldXdim];
  

/* Position:
*  Struktur für die Angabe einer Position im Feld.
*/
  struct Position{
     unsigned short X;
     unsigned short Y;
  };

  
/* EingabeZeichen:
*  Zeichen, dass von stdin über scanf eingelesen wurde.
*/ 
  char EingabeZeichen;
  
  
  
/*    Deklarationen der Methoden    *
*************************************/

/* init:
*  Initialisiert den Inhalt des Feldes und
*  legt die Start-Positionen für Threads fest.
*/
  void init(void);


/* gibStartPosition:
*  Gibt anhand des Argumentes 'ThreadNr' die entsprechende
*  Start-Position im Feld als Struktur 'Position' zurück.
*  Einschränkung: 0 <= ThreadNr <= 9
*/
  struct Position gibStartPosition(unsigned short ThreadNr);


/* gibNeuePosition:
*  Ermittelt anhand des Argumentes 'altePosition' eine neue, freie
*  Position im Feld in unmittelbarer Umgebung der alten Position
*  und übergibt diese als Struktur 'Position' zurück.
*  Sind alle Nachbarstellen belegt, wird die aktuelle (alte)
*  Position übergeben.
*/
  struct Position gibNeuePosition(struct Position altePosition);


/* anzeigen:
*  Löscht die Ausgabe des Terminals und
*  gibt den aktuellen Zustand des Feldes
*  umgeben von einem Rahmen aus.
*  Anschließend wird ein Menü angezeigt.
*/ 
  void anzeigen(void);




  
  
  

#ifdef __STRICT_ANSI__
extern int usleep(int);
#endif

#endif

