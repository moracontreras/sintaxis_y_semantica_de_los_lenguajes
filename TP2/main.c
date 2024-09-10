#include "scanner.h"

void limpiar_lexema(char* lexema) {   // se elimina el /n del lexema
    int len = strlen(lexema);
    if (lexema[len - 1] == '\n') {
        lexema[len - 1] = '\0';
    }
}

int main() {
    int token;
    while ((token = scanner()) != FDT) {
        limpiar_lexema(lexema);  // Limpiar el lexema antes de imprimir
        switch (token) {
            case IDENTIFICADOR:
                printf("Identificador '%s'\n", lexema);
                break;
            case CONSTANTE:
                printf("Constante '%s'\n", lexema);
                break;
            case PUNTO_Y_COMA:
                printf("Punto y coma ';'\n");
                break;
            case PARENTESIS_ABRE:
                printf("Paréntesis que abre '('\n");
                break;
            case PARENTESIS_CIERRA:
                printf("Paréntesis que cierra ')'\n");
                break;
            case COMA:
                printf("Coma ','\n");
                break;
            case ASIGNACION:
                printf("Asignación ':='\n");
                break;
            case MAS:
                printf("Más '+'\n");
                break;
            case MENOS:
                printf("Menos '-'\n");
                break;
            case MULTIPLICACION:
                printf("Multiplicación '*'\n");
                break;
            case ERROR_GENERAL:
                printf("Error general '%s'\n", lexema);
                break;
            case ERROR_ASIGNACION:
                printf("Error en asignación por '%s'\n", lexema);
                break;
            default:
                printf("Token no reconocido o error inesperado.\n");
                break;
        }
    }
    return 0;
}
