// scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef enum {
    FDT = 0,
    IDENTIFICADOR,
    CONSTANTE,
    PUNTO_Y_COMA,
    PARENTESIS_ABRE,
    PARENTESIS_CIERRA,
    COMA,
    ASIGNACION,
    MAS,
    MENOS,
    MULTIPLICACION,
    DIVISION,
    ERROR_GENERAL,
    ERROR_ASIGNACION,
    PROGRAMA,
    FIN,
    ENTERO,
    LEER,
    ESCRIBIR,
    DECLARACION, 
    RESTO
} Token;

typedef struct {
    char *palabra;
    Token token;
} PalabraReservada;

extern bool debo_escanear;

extern PalabraReservada tabla_de_palabras_reservadas[];

extern char lexema[100];
int scanner();
Token prox_token(void);
void match(Token tok);
int buscar(const char *lexema, PalabraReservada *tabla);
void print_error_lexico(Token token_actual, char* c);
void error_sintactico();
void limpiar_lexema(char* lexema);

#endif // SCANNER_H
