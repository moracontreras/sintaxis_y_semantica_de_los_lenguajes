#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

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
    ERROR_GENERAL,
    ERROR_ASIGNACION
} Token;

extern char lexema[100];
int scanner();

#endif // SCANNER_H