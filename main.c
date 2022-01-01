#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "alex.h"
#include "fun_stack.h"
#include "parser.h"


// Wywołanie z {2} gdy podajemy liste funkckji do ignorowanie
//           z {1} gdy takowej listy nie podajemy
// ./a.out 2 <plik_z_listą_funkcji_do_ignorowania> <pliki_analizowane>...
// ./a.out 1 <pliki_analizowane>...
// Kody wyjścia:
// 0 - Prawidłowy kod wyjścia
// 2 - Błąd danych wejściowych

void help(char *nazwa){
	printf("Pomoc\n\n");
	printf("Sposób wywołania:\n %s <tryb> <ign_l> <plik_1> <plik_2> ...\n\n", nazwa);
	printf("<tryb> - Jedna z wartości { 1, 2}. Tryb pierwszy(1) powoduje\n nie wczytywania listy funkcji do ignorowania. Tryb drugi(2) umożliwia\n");
	printf("wpowadzenie listy funkcji do ignorowania.\n\n");
	printf("<ign_l> - Plik posiadający listę funkcji do ignorowania podczas\n analizy plików z programem.\n\n");
	printf("<plik_<indeks>> - Pliki o indeksie <indeks>.\n\n");
}

int main(int argc, char **argv){
	int i, pocz = 0;
	int tryb = argc > 1 ? atoi(argv[1]) : 0;
	if (tryb != 1 && tryb != 2){
		fprintf(stderr, "%s: Nie prawidłowy format wejściowy.\nNie wprowadzono trybu działania programu\n", argv[0]);
		help(argv[0]);
		return 2;
	}
	if (tryb == 2){
		FILE *ignoruj = argc > 2 ? fopen(argv[2], "r") : NULL;
		if (ignoruj == NULL){
			fprintf(stderr, "%s: Nie praiwdłowy format wejściowy.\nNie podano plików wejściowych.\n", argv[0]);
			help(argv[0]);
			return 2;
		}
		pocz++;
	}
	if (argc < 3){
		fprintf(stderr, "%s: Nie praiwdłowy format wejściowy.\nNie podano plików wejściowych.\n", argv[0]); 
		help(argv[0]);
		return 2;
	}
	// Dane wczytane i zaakceptowane	
	for( i = 2 + pocz; i < argc; i++){ // pętla iterująca po plikach argv[i]
<<<<<<< HEAD
=======
		
>>>>>>> c08b4c03b2bee992c20482a75e31e9f4b49fa83f
		analizatorSkladni(argv[i]);
	}
	return 0;
}
