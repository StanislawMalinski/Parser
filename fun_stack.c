#include "fun_stack.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct StosEl{
    int par_level;
    char *funame;
    struct StosEl *next;
} Stos;

int top_of_funstack(){
    int t = top->par_level;
    return t;
}

void put_on_fun_stack( int par_level, char *funame){
    if( top == NULL){
	(*top)->next=&(Stos *) malloc (sizeof(Stos));
	(*top)->funame
	(*top)->next = NULL;
    }else{
	Stos *New;
	New->par_level = par_level;
	New->funame = funame;
	New->next = *top;
	*top = New;
    }
}

char *get_from_stack(){
    char *tmp;
    if( top == NULL)
	fprintf(stderr, "char *get_from_stacks: Stos jest pusty!\n");
    else{
	tmp = top->funame
	free(top->funame);
	free(top->par_level;
	top->next;
	return tmp;
    }
}
