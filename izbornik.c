#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int izbornik() {
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	
	printf("\t\t\tOpcija 1: dodavanje vjezbe!\n");
	printf("\t\t\tOpcija 2: ucitavanje vjezbi!\n");
	printf("\t\t\tOpcija 3: ispisivanje vjezbi!\n");
	printf("\t\t\tOpcija 4: pretrazivanje vjezbi!\n");
	printf("\t\t\tOpcija 5: brisanje vjezbe!\n");
	printf("\t\t\tOpcija 6: brisanje datoteke!\n");
	printf("\t\t\tOpcija 7: izlaz iz programa!\n");
	printf("======================================\
======================================\n");

	int uvijet = 0;
	static VJEZBE* poljeVjezbi = NULL;
	static VJEZBE* pronadenaVjezba = NULL;
	scanf("%d", &uvijet);
	switch (uvijet) {
	case 1:
		dodajVjezbu("trening.bin");
	case 2:
		if (poljeVjezbi != NULL) {
			free(poljeVjezbi);
			poljeVjezbi = NULL;
		}
		poljeVjezbi = (VJEZBE*)ucitavanjeVjezbi("trening.bin");
		if (poljeVjezbi == NULL) {
			exit(EXIT_FAILURE);
		}
		break;
	case 3:
		ispisivanjeVjezbi(poljeVjezbi);
		break;
	case 4:
		pronadenaVjezba= (VJEZBE*)pretrazivanjeVjezbi(poljeVjezbi);
		break;
	case 5:
		brisanjeVjezbe(&pronadenaVjezba, poljeVjezbi, "trening.bin");
		break;
	case 6:
		brisanjeDatoteke("trening.bin");
		break;
	case 7:
		uvijet = izlazIzPrograma(poljeVjezbi);
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}