#ifndef _FUN_STACK_H_IS_INCLUDED_
#define _FUN_STACK_H_IS_INCLUDED_

int top_of_funstack( void ); 
     // zwraca par_level - "zagłębienie nawiasowe"
     // przechowywane na szczycie
void put_on_fun_stack( int par_level, char *funame ); 
     // odkłada na stos 
     // parę (funame,par_level)
char *get_from_fun_stack( void );
     // usuwa z wierzchołka parę 
     // (funame,par_level), zwraca zdjętą funame
#endif

/*
1) Dlaczego w definicjach funckji nie podajemy wskaźnika na stos?
2) Co funkcja *get_from... ma zwracać w przypadku gdy stos jest pusty?
3) Dlaczego funkcja *get_from.. zwraca tylko funame a nie zwraca wskaźnika
	na następny element stosu?
4) Dlaczego nie rozdzielić funkcji *get_from... na funkcje zwracającą 
	funame oraz na funckje usuwającą ostatni element stosu oraz
	zwracającą wskaźnik na następny element. (A w przypadku gdy 
	mamy ostatni element zwraca NULL)
5) Czym się różni typedef struct <nazwa_0> {...} <nazwa_1>; od 
	struct <nazwa> {..};
*/
