all:
	gcc -c -fPIC -std=c99 -g -coverage -O0 src/test.c -o bin/test.o
	gcc -coverage -shared bin/test.o -o bin/libsol.so
	gcc -coverage test/runner.c bin/libsol.so -o bin/runner
	./bin/runner
	mv *.gcda *.gcno bin
	gcov bin/*.gcda
