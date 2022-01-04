#ifndef _PARSER_H_IS_INCLUDED_
#define _PARSER_H_IS_INCLUDED_

typedef struct TYPE         // przechowuje informacje o pojedynczym wystąpieniu jakiejś funkcji
{
    int typ;                //1 - definicja, 2 - prototyp, 3 - wywołanie
    char *nazwa;
    int numer_linii;
    char *plik;
} stat;

typedef struct KONT         // przechowuje informacje o wszystkich wystąpieniach wszystkich funkcji
{
    int size;
    stat *kont;
} kontener;

void analizatorSkladni(char *inpname);                              // analizuje składnię programu

void kontener_pamiec(void);                                         // dynamicznie alokuje pamiec dla kontenera

void store_add_def(char *funame, int line_nr, char *inpname);       // dodaje informacje o definicji funkcji do struktur

void store_add_proto(char *funame, int line_nr, char *inpname);     // dodaje informacje o prototypie funckji do struktur

void store_add_call(char *funame, int line_nr, char *inpname);      // dodaje informacje o wywołaniu funkcji do struktur

int comp(const void *aa, const void *bb);                           // funkcja porównująca dla quicksort

char * typ(int a);                                                  // zamienia typ funkcji z formy numerycznej na słowną

int wypisywacz(void);                                               // wypisuje informacje o funkcjach w programie

#endif
