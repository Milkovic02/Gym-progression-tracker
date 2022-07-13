#ifndef HEADER_H
#define HEADER_H

typedef struct vjezbe {
	int id;
	char imeVjezbe[45];
	int sets;
	int reps;
}VJEZBE;

int izbornik();
void kreiranjeDatoteke();
void dodajVjezbu();
void* ucitavanjeVjezbi();
void ispisivanjeVjezbi(const VJEZBE* const);
void* pretrazivanjeVjezbi(VJEZBE* const);
void brisanjeVjezbe(VJEZBE* poljeVjezbi);
int izlazIzPrograma(VJEZBE*);
int bmibmrCalc();


#endif //HEADER_H


