
#include "aufgabe2.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS	10

pthread_t threadArray[NUM_THREADS];

void* feldThread(void* arg) {

	int i;

	for (i = 0; i < NUM_THREADS; i++) {
		if (pthread_equal(threadArray[i], pthread_self())) {

			struct Position ps = gibStartPosition(i);
			do {

				char tmp = Feld[ps.Y][ps.X];	 // zwischenspeichern des Zeichens aus dem Feld an der aktuellen Position
				struct Position newPS = gibNeuePosition(ps); // neue Position ermitteln
				Feld[newPS.Y][newPS.X] = tmp; // an die neue Position den alten Wert schreiben

				usleep(200000); // 200ms warten

			} while( !((EingabeZeichen == 'b') || (EingabeZeichen == 'B')) );
		}
	}

	pthread_exit(NULL);
}

void* anzeigeThread(void *arg) {

	do {
		anzeigen();
		usleep(30000);
	} while( !((EingabeZeichen == 'b') || (EingabeZeichen == 'B')) );

	pthread_exit(NULL);
}

int main(void) {

	// initialisiere das Feld und die Startpositionen
	init();

	int i;
	// Erzeuge 10 Threads
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_create(&threadArray[i], NULL, &feldThread, NULL);
	}

	// Erzeuge einen anzeigeThread
	pthread_t aThread;
	pthread_create(&aThread, NULL, anzeigeThread, NULL);

	// Abfrage der Eingabe
	do
	{
		scanf(" %c", &EingabeZeichen);

	} while( !((EingabeZeichen == 'b') || (EingabeZeichen == 'B')) );

	// fange alle Threads wieder ein
	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(threadArray[i], NULL);
	}

	pthread_exit(NULL);

	return 0;
}

