#include "tokens.h"

extern int yylex();
extern char* yytext;

const char* token_names[] = {
    "Fin de Archivo", 
    "Identificador", 
    "Constante", 
    "Programa", 
    "Leer", 
    "Escribir",
	"Entero", 
    "Asignación", 
    "Fin"
};


int main(int arg, char* args[]) {
    int token;

    if(arg > 1) {
        yyin = fopen(args[1], "r");
        if (!yyin) {
            printf("Error al abrir el archivo\n");
            return 1;  // Salir si no se puede abrir el archivo
        }
    } else {
        yyin = stdin;  // Usar la entrada estándar solo si no se proporcionó archivo
    }

    do {
        token = yylex();

        switch (token) {
            case IDENTIFICADOR:
            case CONSTANTE:
                printf("Token: %s\tlexema: %s\n", token_names[token], yytext);
                break;

            case FIN:
            case PROGRAMA:
            case LEER:
            case ESCRIBIR:
			case ENTERO:
            case ASIGNACION:
                printf("Token: %s\n", token_names[token], token);
                break;
				
            case 0:
                printf("Token: Fin de Archivo\n");
                break;

            default:
                printf("Token: '%c'\n", token);
                break;
        }
    } while (token != 0);

    if (yyin != stdin) {
        fclose(yyin);  // Cerrar el archivo si se abrió
    }

    return 0;
}