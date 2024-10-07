CC = gcc
CFLAGS = -Wall -g

SCANNER = scanner.l
MAIN_SRC = main.c
HEADERS = tokens.h

LEX = lex.yy.c
EXEC = parser
OUTPUT_FILE = salida.txt 

all: runfile
	# Esperar 2 segundos antes de limpiar
	sleep 1
	make clean_obj

$(LEX): $(SCANNER)
	flex $(SCANNER)

lex.yy.o: $(LEX) $(HEADERS)
	$(CC) $(CFLAGS) -c $(LEX) -o lex.yy.o

main.o: $(MAIN_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o main.o

$(EXEC): lex.yy.o main.o
	$(CC) $(CFLAGS) lex.yy.o main.o -o $(EXEC)

runfile: $(EXEC)
	touch $(OUTPUT_FILE)
	./$(EXEC) entrada.txt > $(OUTPUT_FILE)

clean_obj:
	rm -f *.o

clean:
	rm -f *.o $(LEX) $(EXEC) $(OUTPUT_FILE)
	rm -f *.exe