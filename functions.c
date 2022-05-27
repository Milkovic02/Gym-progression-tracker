#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojVjezbi = 0;

void kreiranjeDatoteke() {
	FILE* pF = NULL;

	pF = fopen("trening.bin", "wb");

	if (pF == NULL) {
		perror("Kreiranje datoteke trening.bin");
	}
	fwrite(&brojVjezbi, sizeof(int), 1, pF);
	fclose(pF);
}

void dodajVjezbu() {
	kreiranjeDatoteke();
	FILE* pF = fopen("trening.bin", "rb+");
	if (pF == NULL) {
		perror("Dodavanje vjezbi u datoteke trening.bin");
		exit(EXIT_FAILURE);
	}
	fread(&brojVjezbi, sizeof(int), 1, pF);

	VJEZBE temp = { 0 };
	getchar();
	printf("Unesite ime vjezbe:\n");
	scanf(" %19[^\n]", temp.imeVjezbe);
	printf("Unesite broj serija:\n");
	scanf("%d", &temp.sets);
	printf("Unesite broj ponavljanja:\n");
	scanf("%d", &temp.reps);

	fseek(pF, sizeof(VJEZBE) * brojVjezbi, SEEK_CUR);
	fwrite(&temp, sizeof(VJEZBE), 1, pF);
	rewind(pF);
	brojVjezbi++;
	fwrite(&brojVjezbi, sizeof(int), 1, pF);
	fclose(pF);
}
void* ucitavanjeVjezbi() {
	FILE* pF = fopen("trening.bin", "rb");
	if (pF == NULL) {
		perror("Nijedna vjezba nije dodana u program.");
		return NULL;
		exit(EXIT_FAILURE);
	}
	fread(&brojVjezbi, sizeof(int), 1, pF);
	VJEZBE* poljeVjezbi = NULL;
	poljeVjezbi = (VJEZBE*)calloc(brojVjezbi, sizeof(VJEZBE));
	if (poljeVjezbi == NULL) {
		perror("Zauzimanje memorije...");
		return NULL;
		exit(EXIT_FAILURE);
	}
	fread(poljeVjezbi, sizeof(VJEZBE), brojVjezbi, pF);
	return poljeVjezbi;
}
void ispisivanjeVjezbi(const VJEZBE* const poljeVjezbi) {

	if (poljeVjezbi == NULL) {
		printf("Nijedna vjezba nije unesena.\n");
		return;
	}
	int i;
	for (i = 0; i < brojVjezbi; i++)
	{
		printf("%45s -> %d serije x %d ponavljanja\n",
			(poljeVjezbi + i)->imeVjezbe,
			(poljeVjezbi + i)->sets,
			(poljeVjezbi + i)->reps);
	}
}
void* pretrazivanjeVjezbi(VJEZBE* const poljeVjezbi) {
	if (poljeVjezbi == NULL) {
		printf("Nema nijedne vjezbe.\n");
		return NULL;
	}
	int i;
	char trazenoIme[20] = { '\0' };
	printf("Pretrazivanje vjezbe:\n");
	getchar();
	scanf(" %19[^\n]", trazenoIme);
	for (i = 0; i < brojVjezbi; i++)
	{
		if (!strcmp(trazenoIme, (poljeVjezbi + i)->imeVjezbe)) {
			printf("Trazena vjezba: %45s", poljeVjezbi + i);
			return (poljeVjezbi + i);
		}
	}
	return NULL;
}

void brisanjeVjezbe(VJEZBE** const trazenaVjezba, const VJEZBE* const poljeVjezbi)
{
	FILE* pF = fopen("trening.bin", "wb");
	if (pF == NULL) {
		perror("Brisanje studenta iz datoteke trening.bin");
		exit(EXIT_FAILURE);
	}
	fseek(pF, sizeof(int), SEEK_SET);
	int i;
	int noviBrojacVjezbi = 0;
	for (i = 0; i < brojVjezbi; i++)
	{
		if (*trazenaVjezba != (poljeVjezbi + i)) {
			fwrite((poljeVjezbi + i), sizeof(VJEZBE), 1, pF);
			noviBrojacVjezbi++;
		}
	}
	rewind(pF);
	fwrite(&noviBrojacVjezbi, sizeof(int), 1, pF);
	fclose(pF);
	printf("Vjezba je uspjesno izbrisana!\n");
	*trazenaVjezba = NULL;
}
void brisanjeDatoteke() {
	printf("Zelite li uistinu obrisati datoteku %s?\n", "trening.bin");
	printf("Utipkajte \"da\" ako uistinu želite obrisati datoteku u suprotno utipkajte\ \"ne\"!\n");
	char potvrda[3] = { '\0' };
	scanf(" %2s", potvrda);
	if (!strcmp("da", potvrda)) {
		remove("trening.bin") == 0 ? printf("Uspjesno obrisana datoteka %s!\n",
			"trening.bin") : printf("Neuspjesno brisanje datoteke %s!\n", "trening.bin");
	}
}
int izlazIzPrograma(VJEZBE* poljeVjezbi) {
	free(poljeVjezbi);
	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int izbornik() {
	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");

	printf("\n\t\t\tOpcija 1: dodavanje vjezbe u program\n");
	printf("\t\t\tOpcija 2: ispisivanje vjezbi!\n");
	printf("\t\t\tOpcija 3: pretrazivanje vjezbi!\n");
	printf("\t\t\tOpcija 4: brisanje vjezbe!\n");
	printf("\t\t\tOpcija 5: brisanje datoteke!\n");
	printf("\n\t\t\tOpcija 0: izlaz iz programa!\n");
	printf("======================================\
======================================\n");

	int uvijet = 0;
	static VJEZBE* poljeVjezbi = NULL;
	static VJEZBE* pronadenaVjezba = NULL;
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 0:
		uvijet = izlazIzPrograma(poljeVjezbi);
		break;
	case 1:
		ucitavanjeVjezbi();
		if (brojVjezbi == 0) {
			kreiranjeDatoteke();
		}
		dodajVjezbu(poljeVjezbi);
		break;
	case 2:
		ispisivanjeVjezbi(poljeVjezbi);
		break;
	case 3:
		pronadenaVjezba = (VJEZBE*)pretrazivanjeVjezbi(poljeVjezbi);
		break;
	case 4:
		brisanjeVjezbe(&pronadenaVjezba, poljeVjezbi, "trening.bin");
		break;
	case 5:
		brisanjeDatoteke("trening.bin");
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}