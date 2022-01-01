all:
	gcc -Wall --pedantic main.c parser.c alex.c fun_stack.c -o dzialacz
test:all
	./dzialacz 1 plik_test.c
	rm dzialacz
testF:
	gcc -Wall --pedantic TFunCH.c fun_stack.c -o test
	./test
	rm test
