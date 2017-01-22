all: grovepi.o Musee.o
	gcc -o bin/Musee obj/grovepi.o obj/Musee.o -lfmod

grovepi.o: src/grovepi.c src/grovepi.h
	gcc -o obj/grovepi.o -c src/grovepi.c

Musee.o: src/Musee.c
	gcc -o obj/Musee.o -c src/Musee.c
