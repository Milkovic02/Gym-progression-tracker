#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

int main(void) {
	kreiranjeDatoteke();
	int uvijet = 1;

	while (uvijet) {
		uvijet = izbornik();
	}

	printf("Zavrsetak programa!\n");
	return 0;
}
