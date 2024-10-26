#include "parser.h"

void parser() {
    programa();
}


void programa() {
    Token token_actual = prox_token();
    if (token_actual == PROGRAMA) {
        match(token_actual);
        match(IDENTIFICADOR);
        printf("Programa: %s\n", lexema);
        lista_declaraciones();
        lista_sentencias();
    }
    
    token_actual = prox_token();
    if (token_actual == FIN) {
        match(FIN);
        printf("fin\n");
    } else {
        error_sintactico_token();
    }
}

void lista_declaraciones() {
    Token token_actual = prox_token();
    if (token_actual == ENTERO) {
        match(ENTERO);
        lista_identificadores();
        match(PUNTO_Y_COMA);
        printf("Sentencia declaración\n");
        lista_declaraciones();
    } else {
        debo_escanear = false;
    }
}

void lista_identificadores() {
    match(IDENTIFICADOR);
    if (prox_token() == COMA) {
        match(COMA);
        lista_identificadores();
    }
}

void lista_sentencias() {
    if (prox_token() == IDENTIFICADOR || prox_token() == LEER || prox_token() == ESCRIBIR) {
        sentencia();
        lista_sentencias();
    }
    else if (prox_token() == ENTERO) {
        lista_declaraciones();
        lista_sentencias();
    }
}
void sentencia() {
    Token token_actual = prox_token();
    switch (token_actual) {
        case IDENTIFICADOR:
        if(prox_token()!=FIN){
            match(IDENTIFICADOR);
            match(ASIGNACION);
            expresion();
            match(PUNTO_Y_COMA);
            printf("Sentencia asignación\n");}
            else{
                match(IDENTIFICADOR);
            }
            break;
        case LEER:
            match(LEER);
            match(PARENTESIS_ABRE);
            printf("Sentencia leer\n");
            lista_identificadores();
            if(prox_token() == PUNTO_Y_COMA){
                match(IDENTIFICADOR);
                match(PUNTO_Y_COMA);
                match(IDENTIFICADOR);
                
                lista_declaraciones();
            }else{
                match(PARENTESIS_CIERRA);
                match(PUNTO_Y_COMA);}
            break;
        case ESCRIBIR:
            match(ESCRIBIR);
            match(PARENTESIS_ABRE);
            lista_expresiones();
            match(PARENTESIS_CIERRA);
            match(PUNTO_Y_COMA);
            printf("Sentencia escribir\n");
            break;
        default:
            error_sintactico_token();
    }
}

void expresion() {
    termino();  // Llamada a "termino"
    while (prox_token() == MAS || prox_token() == MENOS) {
        if (prox_token() == MAS) {
            match(MAS);
            termino();
        } else if (prox_token() == MENOS) {
            match(MENOS);
            termino();
        }
    }
}

void termino() {
    factor();
    while (prox_token() == MULTIPLICACION || prox_token() == DIVISION || prox_token() == RESTO) {
        if (prox_token() == MULTIPLICACION) {
            match(MULTIPLICACION);
            factor();
        } else if (prox_token() == DIVISION) {
            match(DIVISION);
            factor();
        } else if (prox_token() == RESTO) {
            match(RESTO);
            factor();
        }
    }
}

void factor() {
    if (prox_token() == IDENTIFICADOR) {
        match(IDENTIFICADOR);
    } else if (prox_token() == CONSTANTE) {
        match(CONSTANTE);
    } else if (prox_token() == PARENTESIS_ABRE) {
        match(PARENTESIS_ABRE);
        expresion();
        match(PARENTESIS_CIERRA);
    } else if (prox_token() == MENOS) {
        match(MENOS);
        expresion();
    } else {
        if(prox_token()!=FIN){
        error_sintactico();
        match(MULTIPLICACION);
        match(MENOS);
        match(IDENTIFICADOR);}
    }
}

void error_sintactico_token() {
    Token t = prox_token(); 

    printf("Error sintáctico: no se esperaba el token '%s'\n", lexema);

    while (t != PUNTO_Y_COMA && t != FIN && t != FDT && t != PARENTESIS_CIERRA) {
        t = prox_token();
    }
   debo_escanear = true;
}

void lista_expresiones() {
    Token token_actual = prox_token();

    if (token_actual == IDENTIFICADOR || token_actual == CONSTANTE) {
        expresion();
        while (prox_token() == COMA) {
            match(COMA);
                token_actual = prox_token();

                if (token_actual == IDENTIFICADOR || token_actual == CONSTANTE) {
                    expresion();
                } else {
                    printf("Error sintáctico: se esperaba una expresión después de ','\n");
                    error_sintactico_token();
                    break;
                }
            }
    }
        else {
        printf("Error sintáctico: se esperaba una expresión\n");
        error_sintactico_token();
    }
}
