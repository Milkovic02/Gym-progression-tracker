#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "dataType.h"
int izbornik(const char* const);
void kreiranjeDatoteke(const char* const);
void dodajStudenta(const char* const);
void* ucitavanjeStudenata(const char* const);
void ispisivanjeStudenata(const VJEZBE* const);
void* pretrazivanjeStudenata(VJEZBE* const);
void brisanjeStudenta(VJEZBE** const, const VJEZBE* const, const char* const);
void promjenaImenaDatoteci(const char*);
void brisanjeDatoteke(const char*);
int izlazIzPrograma(VJEZBE*);
#endif //FUNCTIONS_H