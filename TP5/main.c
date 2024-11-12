#include <stdio.h>
#include "parser.h"

int yyparse(void);
extern int yynerrs;  
extern int yylexerrs; 
extern FILE* yyin; 

int main() {
    int resultado = yyparse();

    if (resultado == 0 && yynerrs == 0) {
        printf("Compilacion terminada con exito.\n");
    } else {
        printf("Errores de compilacion.\n");
    }
    printf("Errores sintacticos: %d - Errores lexicos: %d\n", yynerrs, yylexerrs);

    return 0;
}