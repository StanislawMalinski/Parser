#include "fun_stack.h"
#include <stdio.h>
#include <stdlib.h>

Layer *top;

int top_of_funstack(){
    int t = top->par_level;
    return t;
}

void put_on_fun_stack( int par_level, char *funame){
    if (top == NULL)
	top = malloc(sizeof(top));
    Layer *New;
    New = malloc(sizeof(Layer));
    New->par_level = par_level;
    New->funame = funame;
    New->next = top;
    top = New;
}

char *get_from_fun_stack(){
    char *tmp;
    Layer *temper;
    if( top->next == NULL){
	fprintf(stderr, "char *get_from_stacks: Stos jest pusty!\n");
	return NULL;
    }else{
	tmp = top->funame;
	temper = top->next;
	top = temper;
	return tmp;
    }
}
