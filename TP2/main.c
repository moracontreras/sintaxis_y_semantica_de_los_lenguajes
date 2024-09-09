#include "scanner.h"

// Función para eliminar '\n' o cualquier otro carácter no deseado al final del lexema
void limpiar_lexema(char* lexema) {
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
        }
    }
    return 0;
}
