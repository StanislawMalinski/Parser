all:
	gcc -Wall --pedantic main.c parser.c alex.c fun_stack.c -o dzialacz
test:all
	./dzialacz 1 parser.c
	rm dzialacz
testF:
	gcc -Wall --pedantic TFunCH.c fun_stack.c -o test
	./test
	rm test
