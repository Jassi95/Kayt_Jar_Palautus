reverse: reverse.o listMaker.o
	gcc -g reverse.o listMaker.o -lm -o reverse -Wall -pedantic -g
reverse.o: reverse.c listMaker.h
	gcc -g reverse.c -c -Wall -pedantic -g
listMaker.o: listMaker.c listMaker.h
	gcc -g listMaker.c -c -Wall -pedantic -g
