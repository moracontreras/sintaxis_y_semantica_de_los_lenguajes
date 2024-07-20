CC = gcc
OBJS = main.o conversion.o tabla.o
CFLAGS = -g -Wall -pedantic-errors -std=c2x 

all: prog
#indica que objetivos deben realizarse si o si, sin importar las dependencias

prog: main.o conversion.o tabla.o
	$(CC) $(CFLAGS) $(OBJS) -o prog 

main.o: main.c conversion.h tabla.h
	$(CC) $(CFLAGS) -c main.c -o main.o

conversion.o: conversion.c conversion.h
	$(CC) $(CFLAGS) -c $< -o $@

tabla.o: tabla.c tabla.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.exe

# Escribes por consola de la forma make run ARGS="<inicio> <fin> {incremento}"
run: prog
	@./prog $(ARGS)

# Escribes por consola de la forma make clean run ARGS="<inicio> <fin> {incremento}"
.PHONY: clean run
