#include <stdio.h>
#include "parser.h"

int yyparse(void);
extern int yynerrs;
extern int yylexerrs;
extern int yysemerrs;

int main() {
    int resultado = yyparse();

    if (resultado != 0 || yynerrs != 0 || yylexerrs != 0 || yysemerrs != 0) {
        printf("Errores sintacticos: %d - Errores lexicos: %d - Errores semanticos: %d\n", yynerrs, yylexerrs, yysemerrs);
    }

    return 0;
}
