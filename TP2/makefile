CC=gcc
CFLAGS=-g -Wall -pedantic-errors -std=c2x 

TARGET=scanner

all: $(TARGET)

$(TARGET): main.o scanner.o
	$(CC) $(CFLAGS) -o $@ main.o scanner.o

main.o: main.c scanner.h
	$(CC) $(CFLAGS) -c main.c

scanner.o: scanner.c scanner.h
	$(CC) $(CFLAGS) -c scanner.c

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET) < entrada.txt > salida.txt
	rm -f *.o 

.PHONY: clean