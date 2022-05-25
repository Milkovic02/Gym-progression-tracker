#ifndef HEADER_H
#define HEADER_H

typedef struct vjezbe {
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
void brisanjeVjezbe(VJEZBE** const trazeniStudent, const VJEZBE* const poljeStudenata);
void brisanjeDatoteke();
int izlazIzPrograma(VJEZBE*);

#endif //HEADER_H

