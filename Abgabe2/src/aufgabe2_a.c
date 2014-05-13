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

	for (i = 0; i < NUM_THREADS-1; i++) {
		if (pthread_equal(threadArray[i], pthread_self())) {

			gibStartPosition(i);
			do {

				usleep(200000);

			} while (EingabeZeichen != 'b' || EingabeZeichen != 'B');
		}
	}

	pthread_exit(NULL);
}

void* anzeigeThread(void *arg) {
	do {
		anzeigen();
		usleep(30000);
	} while (EingabeZeichen != 'b' || EingabeZeichen != 'B');

	pthread_exit(NULL);
}

int main(void) {
	init();

	int status;

	int i;
	for (i = 0; i < NUM_THREADS-1; i++) {
		status = pthread_create(&threadArray[i], NULL, &feldThread, NULL);
	}

	pthread_t anzeigeThread = NULL;
	status = pthread_create(&anzeigeThread, NULL, &anzeigeThread, NULL);

	do {
		scanf("%c", &EingabeZeichen);
		fflush(stdin);
	} while (EingabeZeichen != 'b' || EingabeZeichen != 'B');

	for (i = 0; i < NUM_THREADS; i++) {
		status = pthread_join(threadArray[i], NULL);
	}

	pthread_exit(NULL);

	return 0;
}

