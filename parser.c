#include "parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h> // exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne
#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"  // stos funkcji

#define MAXINDENTLENGHT 256     // maks długość identyfikatora
#define SIZE 1

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
        printf("-> Ident\n");
        char *iname = alex_ident ();             // zapamiętaj identyfikator i patrz co dalej
        lexem_t nlex = alex_nextLexem ();
        if (nlex == OPEPAR) {                    // nawias otwierający - to zapewne funkcja
            printf("-> Opepar(po Ident)\n");
            npar++;
	  printf("odstawiam npar=\"%d\" oraz iname=\"%s\"\n", npar, iname);  
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
      printf("-> Opepar\n");
      npar++;
    }
    break;
    case CLOPAR:{	// zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
      printf("-> Clopar (npar = %d)\n", npar);
      int ln_nr = alex_getLN();
      if (top_of_funstack () == npar) {       // sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
                                                // jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
                                                // za identyfikatorem znajdującym się na wierzchołku stosu
          lexem_t nlex = alex_nextLexem ();     // bierzemy nast leksem
	  printf("Tu jeszcze działa\n");
       //   printf("odstawiam get_from_fun_stack=\"%s\", ln_nr=\"%d\" oraz inpname=\"%s\"\n", get_from_fun_stack(), ln_nr, inpname);
          if (nlex == OPEBRA){   // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
printf("def\n");
	      nbra++;
              store_add_def (get_from_fun_stack (), ln_nr, inpname);
          }else if (nbra == 0 ){   // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
printf("proto\n");
              store_add_proto (get_from_fun_stack (), ln_nr, inpname);
          }else{                  // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
printf("call\n");
              store_add_call (get_from_fun_stack (), ln_nr, inpname);
	  }
      }
      npar--;
    }
    break;
    case OPEBRA:
      printf("-> Opebra (nbra = %d)\n", nbra);
      nbra++;
      break;
    case CLOBRA:
      printf("-> Clobra\n");
      nbra--;
      break;
    case ERROR:{
      printf("-> Error\n");
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
    printf("def = %d\n", Kont->size);
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
    printf("proto = %d\n", Kont->size);
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
    printf("call = %d\n", Kont->size);
}

int comp(const void *aa, const void *bb){
    int c;
    int *a = (int*)aa;
    int *b = (int*)bb;
    stat ak = Kont->kont[*a]; 
    stat bk = Kont->kont[*b];
    c =  strcmp(ak.nazwa,bk.nazwa);
    printf("Ja wielki genialny qsort uważam, że wynikiem comp dla (\"%s\", \"%s\") jest %d\n",ak.nazwa, bk.nazwa, c);
    return c;
/*    if (c != 0)				//Porównanie po nazwie funkcji
	return c;

     if (a.typ < b.typ)			//Porównanie po typie 
	return 1;
    else if (a.typ > b.typ)
	return -1;

    c = strcmp(a.plik,b.plik);
    if (c != 0)				//Porównanie po nazwie pliku
	return c;

    if (a.numer_lini < b.numer_lini)	//Porównianie po numerze lini
        return 1;
    else if (a.numer_lini > b.numer_lini)
        return -1;

  */  return 0;	
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
    for (int i = 0; i < petl; i++){
        printf("nazwa = %s\n", Kont->kont[i].nazwa);
    }
    qsort(Kont->kont, petl, sizeof(stat), comp);

    for (int i = 0; i < petl; i++)
	printf("nazwa = %s\n", Kont->kont[i].nazwa);

    tmp_nazwa = (Kont->kont[0]).nazwa;
    tmp_typ = (Kont->kont[0]).typ;
    tmp_plik = (Kont->kont[0]).plik;
    tmp_numer_lini =  (Kont->kont[0]).numer_lini;

    printf("Funkcja '%s'\n\t%s:\n\t\t%s w linijce %d\n", tmp_nazwa, typ(tmp_typ), tmp_plik, tmp_numer_lini);

    for (int i = 0; i < petl; i++){
//	printf("Nazwa nr.%d to %s\n", i, Kont->kont[i].nazwa);
	temp = Kont->kont[i];
	tmp_numer_lini = temp.numer_lini;
	if (strcmp(temp.nazwa,tmp_nazwa) != 0){
             tmp_nazwa = temp.nazwa;
	     printf("Funkcja '%s'\n",tmp_nazwa);
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
	}
    }
    return 0;
}
