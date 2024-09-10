#include "scanner.h"

char lexema[100];

enum estados { 
    INICIO,
    EN_IDENTIFICADOR,
    EN_CONSTANTE,
    EN_ASIGNACION,
    EN_ERROR
};

int tabla_transicion[5][5] = {
    { EN_IDENTIFICADOR, EN_CONSTANTE, EN_ASIGNACION, EN_ERROR, FDT },
    { EN_IDENTIFICADOR, EN_IDENTIFICADOR, EN_ERROR, EN_ERROR, FDT },
    { EN_ERROR, EN_CONSTANTE, EN_ERROR, EN_ERROR, FDT },
    { EN_ERROR, EN_ERROR, EN_ERROR, EN_ERROR, FDT },
    { EN_ERROR, EN_ERROR, EN_ERROR, EN_ERROR, FDT }
};


int scanner() {
    int estado = INICIO;
    int c;
    int i = 0;

    // Limpiar el lexema antes de comenzar
    memset(lexema, 0, sizeof(lexema));

    while (1) {
        c = getchar();
        
        // Ignorar espacios en blanco y saltos de línea
        if (isspace(c)) {
            if (estado == EN_IDENTIFICADOR || estado == EN_CONSTANTE) {
                ungetc(c, stdin);
                break;
            }
            continue;
        }

        // Ignorar ';', ',', '(', ')' si están dentro de un identificador
        if (c == ';' || c == ',' || c == '(' || c == ')') {
            if (estado == EN_IDENTIFICADOR || estado == EN_CONSTANTE) {
                ungetc(c, stdin);
                break;
            }
        }

        lexema[i++] = c;
        lexema[i] = '\0';  //Le agregamos el \0


        if (isalpha(c)) {
            estado = tabla_transicion[estado][0];
            if (estado != EN_IDENTIFICADOR) {
                break;
            }
        } else if (isdigit(c)) {
            estado = tabla_transicion[estado][1];
            if (estado != EN_CONSTANTE && estado != EN_IDENTIFICADOR) {
                break;
            }
        }
        else if (c == ':') {
            estado = tabla_transicion[estado][2];
            c = getchar();
            if (c == '=') {
                strcat(lexema, "=");
                return ASIGNACION;
            } else {
                ungetc(c, stdin);
                return ERROR_ASIGNACION;
            }
        }
        else if (c == '=') {
            return ERROR_ASIGNACION;
        }
        else if (c == ';') {
            return PUNTO_Y_COMA;
        } else if (c == ',') {
            return COMA;
        } else if (c == '(') {
            return PARENTESIS_ABRE;
        } else if (c == ')') {
            return PARENTESIS_CIERRA;
        } else if (c == '+') {
            return MAS;
        } else if (c == '-') {
            return MENOS;
        } else if (c == '*') {
            return MULTIPLICACION;
        } else if (c == EOF) {
            return FDT;
        } else {
            while (!isspace(c) && !isalnum(c) && c != ';' && c != ',' && c != '(' && c != ')') {
                c = getchar();
                strcat(lexema, (char[2]){c, '\0'});
            }
            ungetc(c, stdin);
            return ERROR_GENERAL;
        }
    }

    if (estado == EN_IDENTIFICADOR) {
        return IDENTIFICADOR;
    } else if (estado == EN_CONSTANTE) {
        return CONSTANTE;
    } else {
        return ERROR_GENERAL;
    }
}