#ifndef SCANNER_H
#define SCANNER_H

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
} TokenType;

extern char lexema[100];
int scanner();

#endif
