
CC = gcc

CFLAGS = -Wall -g

SRC = main.c scanner.c

HEADERS = scanner.h

TARGET = scanner

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

clean-all: clean
	rm -f *.gch