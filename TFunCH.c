#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_stack.h"

int main(int argc, char **argv){
    int n = 4;
    printf("Test:\n Liczba testów do przeprowadzenia: %d.\n\n", n);
    put_on_fun_stack(5, "Test_str_1");
    printf("1/%d Test: funkcja 'put_on_funstack' działa prawidłowo.\n", n);
    if ( 5 == top_of_funstack()){
	printf("2/%d Test: funkcja 'top_of_funstack' działa prawidłowo.\n", n);
    } else {
	fprintf(stderr, "Błąd funkcji 'top_of_funstack'.\n");
	return 1;
    }
    if (strcmp("Test_str_1", get_from_fun_stack()) == 0){
        printf("3/%d Test: funkcja 'get_from_fun_stack' działa prawidłowo.\n", n);
    } else {
        fprintf(stderr, "Błąd funkcji 'get_from_fun_stack'.\n");
        return 2;
    }
    if (NULL == get_from_fun_stack()){
        printf("4/%d Test: funkcja 'get_from_fun_stack' działa prawidłowo.\n", n);
    } else {
        fprintf(stderr, "Błąd funkcji 'get_from_fun_stack'.\n");
        return 2;
    }
    printf("'fun_stac.c/h' działają prawidłowo.\n");
	
    return 0;
}
