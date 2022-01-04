#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h> // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"  // stos funkcji

#define MAXINDENTLENGHT 256     // maks długość identyfikatora
#define SIZE 1

int Help = 0;
int Size = 1;
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
        char *iname = alex_ident ();             // zapamiętaj identyfikator i patrz co dalej
        lexem_t nlex = alex_nextLexem ();
        if (nlex == OPEPAR) {                    // nawias otwierający - to zapewne funkcja
            npar++;
          put_on_fun_stack (npar, iname);      // odłóż na stos funkcji
                                                 // stos f. jest niezbędny, aby poprawnie obsłużyć sytuacje typu
                                                 // f1( 5, f2( a ), f3( b ) )
        }
        else {                  // nie nawias, czyli nie funkcja
          lex = nlex;
          continue;
        }
      }
      break;
    case OPEPAR:{
      npar++;
    }
    break;
    case CLOPAR:{				// zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
      int ln_nr = alex_getLN();
      if (top_of_funstack () == npar) {         // sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
          					// jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
        				        // za identyfikatorem znajdującym się na wierzchołku stosu
          lexem_t nlex = alex_nextLexem ();     // bierzemy nast leksem
          if (nlex == OPEBRA){   // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
                  store_add_def (get_from_fun_stack(), ln_nr, inpname);
          }else if (nbra == 0 ){   // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
                  store_add_proto (get_from_fun_stack(), ln_nr, inpname);
          }else{                  // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
                  store_add_call (get_from_fun_stack(), ln_nr, inpname);
	  } 
        npar--;
	lex = nlex;
    	continue;
	}
    npar--;
    }
    break;
    case OPEBRA:
      nbra++;
      break;
    case CLOBRA:
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
	Kont = malloc(sizeof *Kont);
	Kont->kont = malloc(SIZE * sizeof *(Kont->kont));
	Kont->size = 0;
    }else{
	Size = Size + SIZE;
	Kont->kont = realloc(Kont->kont, Size*sizeof *(Kont->kont));
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
    Kont->kont[Kont->size++] = *New;
}

void store_add_proto(char *funame, int line_nr, char *inpname){
    K();
    stat *New;
    New = malloc(sizeof *New);
    New->typ = 2;
    New->nazwa = funame;
    New->numer_lini = line_nr;
    New->plik = inpname;
    Kont->kont[Kont->size++] = *New;
}

void store_add_call(char *funame, int line_nr, char *inpname){
    K();
    stat *New;
    New = malloc(sizeof *New);
    New->typ = 3;
    New->nazwa = funame;
    New->numer_lini = line_nr;
    New->plik = inpname;
    Kont->kont[Kont->size++] = *New;
}

int comp(const void *aa, const void *bb){
    int c;
    stat *a = (stat *)aa; 
    stat *b = (stat *)bb;
    c = strcmp(a->nazwa,b->nazwa);
    if (c != 0)				//Porównanie po nazwie funkcji
	return c;
    if (a->typ > b->typ)			//Porównanie po typie 
	return 1;
    else if (a->typ < b->typ)
	return -1;
    c = strcmp(a->plik,b->plik);
    if (c != 0)				//Porównanie po nazwie pliku
	return c;
    if (a->numer_lini > b->numer_lini)	//Porównianie po numerze lini
        return 1;
    else if (a->numer_lini < b->numer_lini)
        return -1;
    return 0;
	
}

char *typ(int a){
    if (a == 1)
	return "Definicja";
    else if (a == 2)
	return "Prototyp";
    else if (a == 3)
	return "Wywołanie";
    else
	return "ERROR, nieznany typ";
}

int wypisywacz( void ){
    char *tmp_nazwa, *tmp_plik;
    int tmp_typ, tmp_numer_lini;
    int petl = Kont->size;
    stat temp;

    if (petl < 1){
	fprintf(stderr, "'wypisywacz': kontener pusty.\n");
	return 1;
    }
    qsort(Kont->kont, petl, sizeof(stat), comp);
    tmp_nazwa = (Kont->kont[0]).nazwa;
    tmp_typ = (Kont->kont[0]).typ;
    tmp_plik = (Kont->kont[0]).plik;
    tmp_numer_lini =  (Kont->kont[0]).numer_lini;

    printf("\n\nFunkcja '%s'\n\t%s:\n\t\t%s w linijce %d\n", tmp_nazwa, typ(tmp_typ), tmp_plik, tmp_numer_lini);

    for (int i = 1; i < petl; i++){
	temp = Kont->kont[i];
	tmp_numer_lini = temp.numer_lini;
	if (strcmp(temp.nazwa,tmp_nazwa) != 0){
             tmp_nazwa = temp.nazwa;
	     printf("\n\nFunkcja '%s'\n",tmp_nazwa);
	     tmp_typ = temp.typ;
	     printf("\t%s:\n", typ(tmp_typ));
	     tmp_plik = temp.plik;
	     printf("\t\t%s w linijce %d\n", tmp_plik, tmp_numer_lini);
	} else if (temp.typ != tmp_typ){
             tmp_typ = temp.typ;
             printf("\t%s:\n", typ(tmp_typ));
             tmp_plik = temp.plik;
             printf("\t\t%s w linijce %d\n", tmp_plik, tmp_numer_lini);
	} else if (strcmp(temp.plik, tmp_plik) != 0){
             tmp_plik = temp.plik;
             printf("\t\t%s w linijce %d\n", tmp_plik, tmp_numer_lini);
	}else{
	printf("\t\t%s w linijce %d\n", tmp_plik, tmp_numer_lini);
	}
    }
    return 0;
}
