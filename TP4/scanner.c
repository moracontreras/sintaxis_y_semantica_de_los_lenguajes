#include "scanner.h"

PalabraReservada tabla_de_palabras_reservadas[] = {
    {"programa", PROGRAMA},
    {"fin",           FIN},
    {"entero",     ENTERO},
    {"leer",         LEER},
    {"escribir", ESCRIBIR},
    {NULL, 0}
};
bool debo_escanear = true;
char lexema[100];
static Token token_actual;
int i = 0;

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

    memset(lexema, 0, sizeof(lexema));


    while (1) {
        c = getchar();

        if (isspace(c)) {
            if (estado == EN_IDENTIFICADOR || estado == EN_CONSTANTE) {
                ungetc(c, stdin);
                break;
            }
            continue;
        }

        if (c == ';' || c == ',' || c == '(' || c == ')' || c == '%') {
            if (estado == EN_IDENTIFICADOR || estado == EN_CONSTANTE) {
                ungetc(c, stdin);
                break;
            }
        }

        lexema[i++] = c;
        lexema[i] = '\0';  

        if (isalpha(c)) {
            estado = tabla_transicion[estado][0];
            if (estado != EN_IDENTIFICADOR) {
                break;
            }
        } else if (isdigit(c)) {
            estado = tabla_transicion[estado][1];
            lexema[i - 1] = '\0';
            i--;
            while (isdigit(c)) {
                lexema[i++] = c;
                c = getchar();
            }
            lexema[i] = '\0';
            ungetc(c, stdin);
            if (estado == EN_CONSTANTE) {
                return CONSTANTE;
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
            lexema[i++] = c;
            lexema[i] = '\0';
            return MAS;
        } else if (c == '-') {
            return MENOS;
        } else if (c == '*') {
            return MULTIPLICACION;
        } else if (c == EOF) {
            if(estado == EN_IDENTIFICADOR){
                strcpy(lexema,"fin");
                return IDENTIFICADOR;
                break;
            }else {
            return FDT;}
        } else if (c == '%'){
            return RESTO;
        } 
        else {
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


Token prox_token(void) { 
    if (debo_escanear) {
        token_actual = scanner();
        
        while (token_actual == ERROR_GENERAL || token_actual == ERROR_ASIGNACION) {
            print_error_lexico(token_actual,lexema);
            token_actual = scanner(); 
        }
        debo_escanear = false; 


        if (token_actual == IDENTIFICADOR) {
            int resultado = buscar(lexema, tabla_de_palabras_reservadas); 
            if (resultado != -1) {
                token_actual = resultado; 
            }
        }
    }
    return token_actual;
}

void match(Token tok){
	if (tok != prox_token())
		error_sintactico(prox_token());
	debo_escanear = true;

}

int buscar(const char *lexema, PalabraReservada *tabla) {
    int i = 0;
    while (tabla[i].palabra != NULL) {
        if (strcmp(lexema, tabla[i].palabra) == 0) {
            return tabla[i].token; 
        }
        i++;
    }
    return -1; 
}

void print_error_lexico(Token token_actual, char* palabra){ 
    limpiar_lexema(palabra);
    if(token_actual == ERROR_GENERAL){
        printf("Error general: '%s'\n", palabra);
    }
    else{
        printf("Error de asignación: solo '%s'\n", palabra);}
}

void error_sintactico() {
    Token t = prox_token(); 
    limpiar_lexema(lexema);

    switch(t){
        case IDENTIFICADOR: printf("Error sintactico: no se esperaba el token Identificador ('%s')\n", lexema); break;
        case CONSTANTE: printf("Error sintactico: no se esperaba el token Constnate ('%s')\n", lexema); break;
        case PUNTO_Y_COMA: printf("Error sintactico: no se esperaba el token Punto y Coma ('%s')\n", lexema); break;
        case PARENTESIS_ABRE: printf("Error sintactico: no se esperaba el token Abrir parentesis ('%s')\n", lexema); break;
        case PARENTESIS_CIERRA: printf("Error sintactico: no se esperaba el token Cerrar parentesis ('%s')\n", lexema); break;
        case COMA: printf("Error sintactico: no se esperaba el token Coma ('%s')\n", lexema); break;
        case ASIGNACION: printf("Error sintactico: no se esperaba el token Asignación ('%s')\n", lexema); break;
        case MAS: printf("Error sintactico: no se esperaba el token Mas ('%s')", lexema); break;
        case MULTIPLICACION: printf("Error sintactico: no se esperaba el token Multiplicacion ('%s')\n", lexema); break;
        case MENOS: printf("Error sintactico: no se esperaba el token Menos ('%s')\n", lexema); break;
        case DIVISION: printf("Error sintactico: no se esperaba el token Division ('%s')\n", lexema); break;
        case PROGRAMA: printf("Error sintactico: no se esperaba el token Programa ('%s')\n", lexema); break; 
        case FIN: printf("Error sintactico: no se esperaba el token Fin ('%s')\n", lexema); break;
        case ENTERO: printf("Error sintactico: no se esperaba el token Entero ('%s')\n", lexema); break;
        case LEER: printf("Error sintactico: no se esperaba el token Leer ('%s')\n", lexema); break;
        case ESCRIBIR: printf("Error sintactico: no se esperaba el token Escribir ('%s')\n", lexema); break;
        case DECLARACION: printf("Error sintactico: no se esperaba el token Declaración ('%s')\n", lexema); break;
        case RESTO: printf("Error sintactico: no se esperaba el token Resto ('%s')\n", lexema); break;  
    }
}

void limpiar_lexema(char* lexema) {
    int len = strlen(lexema);
    if (lexema[len - 1] == '\n') {
        lexema[len - 1] = '\0';
    }
}