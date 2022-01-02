#include<stdio.h>

// Pierwszy komentarz
/* 
   Drugi komentarz
*/

char *globaly_str = "Bardzo wazny \n globalny str \\ pod żadnym pozorem nie usuwac.\n";

int funkcja1(int a, int b);
double funkcja2(double a, double b);

int main()
{
	int l1 = 5, l2 = 3;
	double l3 = 3.4, l4 = 2.8;

	printf("Wynik dodawania liczb calkowitych %d i %d: %d\n", l1, l2, funkcja1(l1, l2));
	printf("Wynik mnozenia liczb zmiennoprzecinkowych %f i %f: %f\n", l3, l4, funkcja2(l3, l4));

	return 0;
}

int funkcja1(int a, int b)
{
	return a+b;
}

double funkcja2(double a, double b)
{
	return a+b;
}
