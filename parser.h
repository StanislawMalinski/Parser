#ifndef _PARSER_H_IS_INCLUDED_
#define _PARSER_H_IS_INCLUDED_

typedef struct TYPE{
    int typ;              //1 - definicja, 2 - prototyp, 3 - wywołanie
    char *nazwa;
    int numer_lini;
    char *plik;
}stat;

typedef struct KONT{
    int size;
    stat *kont;
}kontener;

void analizatorSkladni(char *inpname);

void store_add_def(char *funame, int line_nr, char *inpname);

void store_add_proto(char *funame, int line_nr, char *inpname);

void store_add_call(char *funame, int line_nr, char *inpname);

int wypisywacz( void );

#endif
