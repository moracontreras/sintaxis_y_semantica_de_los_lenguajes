prog: main.o scanner.o parser.o semantic.o symbol.o
	gcc parser.c scanner.c main.c semantic.c symbol.c -o parser -L/C/msys64/usr/lib -lfl

main.o: main.c scanner.c parser.c semantic.h symbol.h
	gcc -c main.c

scanner.o: scanner.c parser.h
	gcc -c scanner.c

parser.o: parser.c scanner.h semantic.h symbol.h
	gcc -c parser.c

semantic.o: semantic.c semantic.h symbol.h
	gcc -c semantic.c

symbol.o: symbol.c symbol.h
	gcc -c symbol.c

scanner.c scanner.h: scanner.l
	flex scanner.l

parser.c parser.h: parser.y
	bison -d parser.y -o parser.c

clean:
	rm -f parser main.o scanner.o parser.o semantic.o symbol.o scanner.c scanner.h parser.c parser.h
