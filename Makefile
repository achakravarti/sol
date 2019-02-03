all:
	mkdir -p bin
	gcc -c -fPIC -std=c99 -g -coverage -O0 src/test.c -o bin/test.o
	gcc -coverage -shared bin/test.o -o bin/libsol.so
	gcc -coverage test/runner.c bin/libsol.so -lgcov -o bin/runner
	bin/runner
	mv *gcda *gcno bin
	gcov -o bin bin/runner.gcda
	gcov -o bin bin/test.gcda
	ls
	ls bin
	gcc --version
	gcov --version
	find  /usr/lib/gcc -name libgcov.a

