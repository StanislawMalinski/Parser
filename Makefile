all:
	gcc -Wall --pedantic main.c parser.c alex.c fun_stack.c -o dzialacz
	./dzialacz
	rm dzialacz
test:
	gcc -Wall --pedantic TFunCH.c fun_stack.c -o test
	./test
	rm test
