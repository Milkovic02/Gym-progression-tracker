#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

static int brojVjezbi = 0;

void kreiranjeDatoteke() {
	FILE* fp = NULL;
	fp = fopen("trening.bin", "wb");

	if (fp == NULL) {
		perror("Kreiranje datoteke trening.bin");
	}
	fwrite(&brojVjezbi, sizeof(int), 1, fp);
	fclose(fp);
}

void dodajVjezbu() {
	FILE* fp = fopen("trening.bin", "rb+");
	if (fp == NULL) {
		kreiranjeDatoteke();
	}

	if (fp == NULL) {
		perror("Dodavanje vjezbi u datoteke trening.bin");
		exit(EXIT_FAILURE);
	}
	fread(&brojVjezbi, sizeof(int), 1, fp);

	VJEZBE temp = { 0 };
	getchar();
	printf("Unesite ime vjezbe:\n");
	scanf(" %19[^\n]", temp.imeVjezbe);
	printf("Unesite broj serija:\n");
	scanf("%d", &temp.sets);
	printf("Unesite broj ponavljanja:\n");
	scanf("%d", &temp.reps);

	fseek(fp, sizeof(VJEZBE) * brojVjezbi, SEEK_CUR);
	fwrite(&temp, sizeof(VJEZBE), 1, fp);
	rewind(fp);
	brojVjezbi++;
	fwrite(&brojVjezbi, sizeof(int), 1, fp);
	fclose(fp);
}
void* ucitavanjeVjezbi() {
	FILE* fp = fopen("trening.bin", "rb");
	if (fp == NULL) {
		perror("Nijedna vjezba nije dodana u program.");
		return NULL;
		exit(EXIT_FAILURE);
	}

	fread(&brojVjezbi, sizeof(int), 1, fp);
	VJEZBE* poljeVjezbi = NULL;
	poljeVjezbi = (VJEZBE*)calloc(brojVjezbi, sizeof(VJEZBE));
	if (poljeVjezbi == NULL) {
		perror("Zauzimanje memorije...");
		return NULL;
		exit(EXIT_FAILURE);
	}
	fread(poljeVjezbi, sizeof(VJEZBE), brojVjezbi, fp);
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
	FILE* fp = fopen("trening.bin", "wb");
	if (fp == NULL) {
		perror("Brisanje vjezbi iz datoteke trening.bin");
		exit(EXIT_FAILURE);
	}
	fseek(fp, sizeof(int), SEEK_SET);
	int i;
	int noviBrojacVjezbi = 0;
	for (i = 0; i < brojVjezbi; i++)
	{
		if (*trazenaVjezba != (poljeVjezbi + i)) {
			fwrite((poljeVjezbi + i), sizeof(VJEZBE), 1, fp);
			noviBrojacVjezbi++;
		}
	}
	rewind(fp);
	fwrite(&noviBrojacVjezbi, sizeof(int), 1, fp);
	fclose(fp);
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

int glavniIzbornik() {

	printf("/======- Odaberite opciju -======\\\n");
	printf(" |\t\t\t\t|");
	printf("\n |\t1. Odabir treninga\t|\n"); //
	printf(" |\t2. BMI\t\t\t|\n");
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
		kreiranjeDatoteke();
		treningIzbornik();
		break;
	case 2:
		bmiCalc();
		break;
	case 3:

		break;
	case 4:

		break;
	default:
		printf("Odabrali ste opciju koja ne postoji.");
		glavniIzbornik();
	}
	return uvijet;
}

int treningIzbornik() {

	printf("/================================\\\n");
	printf(" |\t\t\t\t|");
	printf("\n |\t1) TRENING 1\t\t|\n");
	printf(" |\t2) TRENING 2\t\t|\n");
	printf(" |\t3) TRENING 3\t\t|\n");
	printf(" |\t4) TRENING 4\t\t|\n");
	printf(" |\t5) TRENING 5\t\t|\n");
	printf(" |\t6) TRENING 6\t\t|\n");
	printf(" |\t7) TRENING 7\t\t|\n");
	printf(" |\t\t\t\t|\n");
	printf(" |\t\t\t\t|\n");
	printf(" |\t0) Povratak na izbornik\t|\n");
	printf(" |______________________________|\n");

	int uvijet;
	printf("Unesite broj: ");
	scanf("%d", &uvijet);
	system("cls");

	switch (uvijet) {
	case 0:
		glavniIzbornik():
		break;
	case 1:
		
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	case 6:

		break;
	case 7:

		break;
	default:
		printf("Odabrali ste opciju koja ne postoji.");
		treningIzbornik();
	}

	return uvijet;
}

int treningMenu() {



}

int bmiCalc() {
	
	int bmr = 0;
	float weight, height, bodyfat, bmi = 0;
	int age;
	char gender;

	printf("Unesite svoje godine: ");
	scanf("%d", &age);
	printf("Unesite svoj spol [M/F]: ");
	scanf("%s", &gender);

	printf("Unesite svoju kilazu [kg]: ");
	scanf("%f", &weight);
	printf("Unesite svoju visinu [cm]: ");
	scanf("%f", &height);
	printf("[NEOBAVEZNO] Unesite svoj postotak masti [%%]: ");
	scanf("%f", &bodyfat);

	if (gender == 'M') {
		bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
	}
	
	if (gender == 'F') {
		bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
	}
	float mheight = height / 100;
	float msqheight = mheight * mheight;

	bmi = weight / msqheight;

	printf("BMI: %f\n", bmi);
	printf("BMR: %d kalorija", bmr);

}
