#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_stack.h"

int main(int argc, char **argv){
    int n = 4;
    printf("Test:\n Liczba testów do przeprowadzenia: %d.\n\n", n);

    printf("Test 1: funkcja 'put_on_fun_stack' - włożenie pary liczba, napis na stos.\n");
    put_on_fun_stack(5, "Test_str_1");
    put_on_fun_stack(10, "Test_str_2");
    printf("1/%d Test: funkcja 'put_on_fun_stack' działa prawidłowo.\n", n);
   
    printf("Test 2: funkcja 'top_of_funstack' - sprawdzenie liczby na wierzchołku stosu.\n");
    if (top_of_funstack() == 10){
    	printf("2/%d Test: funkcja 'top_of_funstack' działa prawidłowo.\n", n);
    } else {
    	fprintf(stderr, "Błąd funkcji 'top_of_funstack'.\n");
    	return 1;
    }
    
    printf("Test 3: funkcja 'get_from_fun_stack' - zdjęcie pary ze stosu i sprawdzenie zdjętego napisu.\n");
    if (strcmp("Test_str_2", get_from_fun_stack()) == 0 && strcmp("Test_str_1", get_from_fun_stack()) == 0){
        printf("3/%d Test: funkcja 'get_from_fun_stack' działa prawidłowo.\n", n);
    } else {
        fprintf(stderr, "Błąd funkcji 'get_from_fun_stack'.\n");
        return 2;
    }

    printf("Test 4: funkcja 'get_from_fun_stack' - stos pusty, wypisanie komunikatu.\n");
    if (get_from_fun_stack() == NULL){
        printf("4/%d Test: funkcja 'get_from_fun_stack' działa prawidłowo.\n", n);
    } else {
        fprintf(stderr, "Błąd funkcji 'get_from_fun_stack'.\n");
        return 2;
    }

    printf("\n'fun_stack.c/h' działają prawidłowo.\n");
	
    return 0;
}
