#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

int main(void) {

	int uvijet = 1;

	while (uvijet) {
		uvijet = glavniIzbornik();
	}

	printf("Zavrsetak programa!\n");
	return 0;
}
