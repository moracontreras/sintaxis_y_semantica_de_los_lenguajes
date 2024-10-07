#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>

typedef enum {
    FDT,        // Fin de texto
    IDENTIFICADOR,
    CONSTANTE,
    PROGRAMA,
    LEER,
    ESCRIBIR,
	ENTERO,
    ASIGNACION,  // ":="
    FIN          
} Token;

extern FILE* yyin;

#endif // SCANNER_H
