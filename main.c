#include "parser.h"
#include "alex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 20

// Wywołanie z {2}, gdy podajemy listę funkcji do ignorowania
//           z {1}, gdy takowej listy nie podajemy
// ./a.out 2 <plik_z_listą_funkcji_do_ignorowania> <pliki_analizowane>...
// ./a.out 1 <pliki_analizowane>...
// Kody wyjścia:
// 0 - Prawidłowy kod wyjścia
// 2 - Błąd danych wejściowych

void help(char *nazwa)
{
	printf("Pomoc\n\n");
	printf("Sposób wywołania:\n %s <tryb> <ign_l> <plik_1> <plik_2> ...\n\n", nazwa);
	printf("<tryb> - Jedna z wartości {1, 2}. Tryb pierwszy(1) powoduje\n niewczytywanie listy funkcji do ignorowania. Tryb drugi(2) umożliwia\n");
	printf("wprowadzenie listy funkcji do ignorowania.\n\n");
	printf("<ign_l> - Plik zawierający listę funkcji do ignorowania podczas\n analizy plików z programem.\n\n");
	printf("<plik_<indeks>> - Pliki do analizy o indeksie <indeks>.\n\n");
}

int main(int argc, char **argv)
{
	char buf[BUF];
	int i, pocz = 0;
	int tryb = argc > 1 ? atoi(argv[1]) : 0;
	if(tryb != 1 && tryb != 2){
		fprintf(stderr, "%s: Nieprawidłowy format wejściowy.\nNie wprowadzono trybu działania programu.\n", argv[0]);
		help(argv[0]);
		return 2;
	}
	if(tryb == 2)
    {
		pocz++;
		FILE *ignoruj = argc > 2 ? fopen(argv[2], "r") : NULL;
		if(ignoruj == NULL)
        {
			fprintf(stderr, "%s: Niepraiwdłowy format wejściowy.\nNie podano plików wejściowych.\n", argv[0]);
			help(argv[0]);
			return 2;
		}
		while(fgets(buf, BUF, ignoruj) != NULL && *buf != '\n')
        {
			if(buf[strlen(buf)-1] == '\n')
				buf[strlen(buf)-1] = '\0';
			dod_key(buf);
		}
		fclose(ignoruj);
	}
	if(argc < 3)
    {
		fprintf(stderr, "%s: Niepraiwdłowy format wejściowy.\nNie podano plików wejściowych.\n", argv[0]); 
		help(argv[0]);
		return 2;
	}
	// dane wczytane i zaakceptowane	
	for(i = 2 + pocz; i < argc; i++)        // pętla iterująca po plikach do analizy (przetestowano dla 1 pliku, według polecenia)
    {
		analizatorSkladni(argv[i]);
	}
	wypisywacz();                           // wypisanie wyników analizy

	return 0;
}
