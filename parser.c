#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h> // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"  // stos funkcji

#define MAXINDENTLENGHT 256     // maks długość identyfikatora
#define SIZE 1

#define MAX

int Size = SIZE;
kontener *Kont;

void
analizatorSkladni (char *inpname)
{                               // przetwarza plik inpname
  FILE *in = fopen (inpname, "r");

  int nbra = 0;   // bilans nawiasów klamrowych {}
  int npar = 0;   // bilans nawiasów zwykłych ()

  alex_init4file (in);          // ustaw analizator leksykalny, aby czytał in
  lexem_t lex;

  lex = alex_nextLexem ();      // pobierz następny leksem
  while (lex != EOFILE) {
    switch (lex) {
    case IDENT:{
	printf("-> Ident\n");
        char *iname = alex_ident ();   // zapamiętaj identyfikator i patrz co dalej
        lexem_t nlex = alex_nextLexem ();
        if (nlex == OPEPAR) {   // nawias otwierający - to zapewne funkcja
          npar++;
          put_on_fun_stack (npar, iname);       // odłóż na stos funkcji
                                                // stos f. jest niezbędny, aby poprawnie obsłużyć sytuacje typu
                                                // f1( 5, f2( a ), f3( b ) )
        }
        else {                  // nie nawias, czyli nie funkcja
          lex = nlex;
          continue;
        }
      }
      break;
    case OPEPAR:
        printf("-> Opepar\n");
      npar++;
      break;
    case CLOPAR:{              // zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
        printf("-> Clopar (npar = %d)\n", npar);
        if (top_of_funstack () == npar) {       // sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
                                                // jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
                                                // za identyfikatorem znajdującym się na wierzchołku stosu
          lexem_t nlex = alex_nextLexem ();     // bierzemy nast leksem
          if (nlex == OPEBRA)   // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
            store_add_def (get_from_fun_stack (), alex_getLN (), inpname);
          else if (nbra == 0)   // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
            store_add_proto (get_from_fun_stack (), alex_getLN (), inpname);
          else                  // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
            store_add_call (get_from_fun_stack (), alex_getLN (), inpname);
        }
        npar--;
      }
      break;
    case OPEBRA:
        printf("-> Opebra\n");
      nbra++;
      break;
    case CLOBRA:
        printf("-> Clobra (nbra = %d)\n", nbra);
      nbra--;
      break;
    case ERROR:{
        printf("-> ERROR\n");
        fprintf (stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
                 "W pliku %s (linia %d) są błędy składni.\n"
                 "Kończę!\n\n", inpname, alex_getLN ());
        exit (1);               // to nie jest najlepsze, ale jest proste ;-)
      }
      break;
    default:
      break;
    }
    lex = alex_nextLexem ();
  }
}

void K( void ){
    if (Kont == NULL){
	Kont = malloc(SIZE *sizeof *Kont);
	Kont->size = 0;
    }else{
	Size = Size + SIZE;
	Kont = realloc(Kont, Size*sizeof *Kont);
    }
}

void store_add_def(char *funame, int line_nr, char *inpname){
    K();
    stat *New;
    New = malloc(sizeof *New);
    New->typ = 1;
    New->nazwa = funame;
    New->numer_lini = line_nr;
    New->plik = inpname;
    Kont->kont[(Kont->size)++] = *New;
}

void store_add_proto(char *funame, int line_nr, char *inpname){
    K();
    stat *New;
    New = malloc(sizeof *New);
    New->typ = 2;
    New->nazwa = funame;
    New->numer_lini = line_nr;
    New->plik = inpname;
    Kont->kont[(Kont->size)++] = *New;
}

void store_add_call(char *funame, int line_nr, char *inpname){
    K();
    stat *New;
    New = malloc(sizeof *New);
    New->typ = 3;
    New->nazwa = funame;
    New->numer_lini = line_nr;
    New->plik = inpname;
    Kont->kont[(Kont->size)++] = *New;
}

int comp(const void *aa, const void *bb){
    int c;
    stat a = Kont->kont[*(int*)aa]; 
    stat b = Kont->kont[*(int*)bb];
    c = strcmp(a.nazwa,b.nazwa);
    if (c != 0)				//Porównanie po nazwie funkcji
	return c;
    if (a.typ > b.typ)			//Porównanie po typie 
	return 1;
    else if (a.typ < b.typ)
	return -1;
    c = strcmp(a.plik,b.plik);
    if (c != 0)				//Porównanie po nazwie pliku
	return c;
    if (a.numer_lini > b.numer_lini)	//Porównianie po numerze lini
        return 1;
    else if (a.numer_lini < b.numer_lini)
        return -1;
    return 0;
	
}

char *typ(int a){
    if (a == 1)
	return "definicja";
    else if (a == 2)
	return "prototyp";
    else if (a == 3)
	return "wywołanie";
    else
	return "ERROR, nieznany typ";
}

int wypisywacz(kontener *COS){
    char *tmp_nazwa;
    int tmp_typ;
    int petl = COS->size;
    if (petl < 1){
	fprintf(stderr, "'wypisywacz': kontener pusty.\n");
	return 1;
    }
    qsort(COS, petl, sizeof(stat), comp);
    tmp_nazwa = (COS->kont[0]).nazwa;
    tmp_typ = (COS->kont[0]).typ;
    //Dalszy kod
    return 0;
}
