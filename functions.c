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
	temp.id = brojVjezbi + 1;

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

void* pretrazivanjeVjezbi(VJEZBE* poljeVjezbi) {

	if (poljeVjezbi == NULL) {
		printf("Polje vjezbi je prazno");
		return NULL;
	}

	char trazenaVjezba[45];
	int i, provjera = 0, brojac = 0;

	printf("Unesite ime vjezbe: ");
	scanf(" %45[^\n]", trazenaVjezba);

	system("cls");

	for (i = 0; i < brojVjezbi; i++) {
		if (strcmp(trazenaVjezba, (poljeVjezbi + i)->imeVjezbe) == 0) {
			provjera++;
			printf("TRAZENA VJEZBA\n");
			printf("%45s -> %d serije x %d ponavljanja\n",
				(poljeVjezbi + i)->imeVjezbe,
				(poljeVjezbi + i)->sets,
				(poljeVjezbi + i)->reps);
		}
	}

	if (provjera == 0) {
		printf("Nije pronadena niti jedna vjezba imena: '%s'.", trazenaVjezba);
	}
	return NULL;
}



void brisanjeVjezbe(VJEZBE* poljeVjezbi) {
	int i, trazenaVjezba, brojac = 0;

	printf("|0 za izlazak, -1 za brisanje svih vjezbi|\nUnesite redni broj vjezbe: ");
	scanf(" %d", &trazenaVjezba);
	if (trazenaVjezba != 0) {
		FILE* fp = NULL;
		fp = fopen("trening.bin", "wb");
		if (fp == NULL) {
			perror("Brisanje");
			exit(EXIT_FAILURE);
		}

		if (trazenaVjezba != -1) {
			rewind(fp);
			fseek(fp, sizeof(int), SEEK_SET);
			for (i = 0; i < brojVjezbi; i++) {
				if (trazenaVjezba != (poljeVjezbi + i)->id) {
					fwrite((poljeVjezbi + i), sizeof(VJEZBE), 1, fp);
					brojac++;
				}
			}
			system("cls");
			if (brojac != 0)
				printf("%d. vjezba uspjesno izbrisana.", trazenaVjezba);
			else
				printf("%d. vjezba ne postoji.", trazenaVjezba);
		}
		else {
			rewind(fp);
			fseek(fp, sizeof(int), SEEK_SET);
			for (int i = 0; i < brojVjezbi; i++) {
				fwrite((poljeVjezbi + i), sizeof(VJEZBE), 1, fp);
			}
			system("cls");
			printf("Sve vjezbe izbrisane.");
		}
		rewind(fp);
		fwrite(&brojac, sizeof(int), 1, fp);
		fclose(fp);
	}
	else {
		system("cls");
		printf("Brisanje otkazano.");
	}

}


int izlazIzPrograma(VJEZBE* poljeVjezbi) {
	free(poljeVjezbi);
	return 0;
}


int izbornik() {
	int uvijet = 0;
	static VJEZBE* poljeVjezbi = NULL;
	static VJEZBE* pronadjeniVlak = NULL;
	FILE* fp = NULL;
	fp = fopen("trening.bin", "rb");
	fread(&brojVjezbi, sizeof(int), 1, fp);

	printf("\n---------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t      Odaberite opciju: \n\n");
	printf("\t\t\t\t  1 : Dodavanje vjezbe u program\n");
	printf("\t\t\t\t  2 : Ispisivanje svih vjezbi\n");
	printf("\t\t\t\t  3 : Pretrazivanje vjezbi\n");
	printf("\t\t\t\t  4 : Brisanje vjezbi iz programa\n");
	printf("\t\t\t\t  5 : BMI & BMR\n\n");

	printf("\t\t\t\t  0 : Izlaz\n");
	printf("---------------------------------------------------------------------------------------------------------\n");

	printf("ODABIR: ");

	scanf(" %d", &uvijet);
	system("cls");

	switch (uvijet) {

	case 0:
		izlazIzPrograma(poljeVjezbi);
		break;

	case 1:
		if (brojVjezbi == 0) {
			kreiranjeDatoteke();
		}
		if (poljeVjezbi != NULL) {
			free(poljeVjezbi);
			poljeVjezbi = NULL;
		}
		poljeVjezbi = (VJEZBE*)ucitavanjeVjezbi();
		fclose(fp);
		dodajVjezbu(poljeVjezbi);
		break;

	case 2:
		fclose(fp);
		if (poljeVjezbi != NULL) {
			free(poljeVjezbi);
			poljeVjezbi = NULL;
		}
		poljeVjezbi = (VJEZBE*)ucitavanjeVjezbi();
		ispisivanjeVjezbi(poljeVjezbi);
		break;

	case 3:
		fclose(fp);
		pretrazivanjeVjezbi(poljeVjezbi);
		break;

	case 4:
		fclose(fp);
		brisanjeVjezbe(poljeVjezbi);
		break;
	case 5:
		fclose(fp);
		bmibmrCalc();
		break;

	default:
		printf("Odabrana opcija ne postoji.");
		break;
	}


	return uvijet;

}



int bmibmrCalc() {
	
	int bmr = 0, uvijet, age;
	float weight, height, bmi = 0;
	char gender;

	printf("Unesite svoje godine: ");
	scanf("%d", &age);
	printf("Unesite svoj spol [M/F]: ");
	scanf("%s", &gender);

	printf("Unesite svoju kilazu [kg]: ");
	scanf("%f", &weight);
	printf("Unesite svoju visinu [cm]: ");
	scanf("%f", &height);

	if (gender == 'M') {
		bmr = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
	}
	
	if (gender == 'F') {
		bmr = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
	}

	float mheight = height / 100;
	float msqheight = mheight * mheight;

	bmi = weight / msqheight;

	printf("\nBMI: %f\n", bmi);
	printf("BMR: %d kalorija\n", bmr);
	printf("\nUpisite 1 za povratak na izbornik: ");
	scanf("%d", &uvijet);

	if (uvijet == 1) {
		system("cls");
		izbornik();
	}

	return uvijet;
}
