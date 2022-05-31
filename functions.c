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
	FILE* pF = fopen("trening.bin", "rb+");
	if (pF == NULL) {
	kreiranjeDatoteke();
	}
	
	
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
		printf("Polje vjezbi je prazno");
		return;
	}

	if (brojVjezbi == 0) {
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


void brisanjeTreninga(VJEZBE** const trazenaVjezba, const VJEZBE* const poljeVjezbi)
{
	FILE* pF = fopen("trening.bin", "wb");
	if (pF == NULL) {
		perror("Brisanje vjezbi iz datoteke trening.bin");
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
	printf("Utipkajte \"da\" ako uistinu �elite obrisati datoteku u suprotno utipkajte\ \"ne\"!\n");
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

int glavniIzbornik() {

	printf("/======- Odaberite opciju -======\\\n");
	printf(" |\t\t\t\t|");
	printf("\n |\t1. Odabir treninga\t|\n"); //
	printf(" |\t2. Tezina i visina\t|\n");
	printf(" |\t3. Prikaz napretka\t|\n");
	printf(" |\t\t\t\t|\n");
	printf(" |\t0. Izlaz iz programa!\t|\n");
	printf(" |______________________________|\n");

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
		treningIzbornik();
		break;
	case 2:
		ispisivanjeVjezbi(poljeVjezbi);
		break;
	case 3:
		brisanjeTreninga(&pronadenaVjezba, poljeVjezbi);
		break;
	case 4:
		brisanjeDatoteke("trening.bin");
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}

int treningIzbornik() {

	printf("/================================\\\n");
	printf(" |\t\t\t\t|");
	printf("\n |\t1) TRENING 1\t\t|\n"); //
	printf(" |\t2) TRENING 2\t\t|\n");
	printf(" |\t3) TRENING 3\t\t|\n");
	printf(" |\t4) TRENING 4\t\t|\n");
	printf(" |\t5) TRENING 5\t\t|\n");
	printf(" |\t6) TRENING 6\t\t|\n");
	printf(" |\t7) TRENING 7\t\t|\n");
	printf(" |\t\t\t\t|\n");
	printf(" |\t0) Povratak na izbornik\t|\n");
	printf(" |______________________________|\n");

}
