all:
	gcc -Wall --pedantic main.c parser.c alex.c fun_stack.c -o Parser
test1:all
	./Parser 1 plik_test.c
	rm Parser
test2:all
	./Parser 2 ign plik_test.c
	rm Parser
testF:
	gcc -Wall --pedantic TFunCH.c fun_stack.c -o test
	./test
	rm test
