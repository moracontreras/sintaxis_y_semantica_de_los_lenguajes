prog: main.o scanner.o parser.o 
	gcc parser.c scanner.c main.c -o parser -L/C/msys64/usr/lib -lfl

main.o: main.c scanner.c parser.c
	gcc -c main.c

scanner.o: scanner.c parser.h
	gcc -c scanner.c

parser.o: parser.c scanner.h
	gcc -c parser.c

scanner.c scanner.h: scanner.l
	flex scanner.l

parser.c parser.h: parser.y
	bison parser.y

clean:
	rm scanner.c parser.c scanner.h parser.h scanner.o parser.o main.o prog


