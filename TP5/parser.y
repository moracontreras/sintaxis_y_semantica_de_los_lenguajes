%{
#include "scanner.h"
%}
%code provides {
void yyerror(const char *msg);
extern int yylexerrs;
}

%defines "parser.h"
%output "parser.c"
%define parse.error verbose

%union {
    char *str;
}

%token <str> PROGRAMA FIN ENTERO LEER ESCRIBIR ID CTE
%token MAS MENOS MULTIPLICACION DIVISION MODULO
%token ASIGNACION PAREN_IZQ PAREN_DER COMA PUNTO_Y_COMA FDT

%type <str> programa expresion termino primaria 

%left MAS MENOS
%left MULTIPLICACION DIVISION MODULO
%precedence NEG

%%
todo	: programa {if (yynerrs || yylexerrs) YYABORT;}
programa: PROGRAMA ID {printf("programa: %s\n", $2);} lista_sentencias FIN 
;

lista_sentencias: sentencia
    | lista_sentencias sentencia
;

sentencia:
    declaracion
    | asignacion
    | lectura
    | escritura
    | error PUNTO_Y_COMA
;

declaracion:
    ENTERO ID PUNTO_Y_COMA {printf("Sentencia declaracion: %s\n", $2);}
;

asignacion:
    ID ASIGNACION expresion PUNTO_Y_COMA {printf("Sentencia asignacion\n");}
;

lectura:
    LEER PAREN_IZQ lista_identificadores PAREN_DER PUNTO_Y_COMA {printf("Sentencia leer\n");}
;

escritura:
    ESCRIBIR PAREN_IZQ lista_expresiones PAREN_DER PUNTO_Y_COMA {printf("Sentencia escribir\n");}
;

lista_identificadores:
    ID
    | lista_identificadores COMA ID
;

lista_expresiones:
    expresion
    | lista_expresiones COMA expresion
;

expresion:
    expresion MAS termino {printf("suma\n");}
    | expresion MENOS termino {printf("resta\n");}
    | termino
;

termino:
    termino MULTIPLICACION primaria {printf("multiplicacion\n");}
    | termino DIVISION primaria {printf("division\n");}
    | termino MODULO primaria {printf("modulo\n");}
    | primaria
;

primaria:
    CTE
    | ID
    | MENOS primaria %prec NEG {printf("inversion\n");}
    | PAREN_IZQ {printf("abre parentesis\n");} expresion PAREN_DER {printf("cierra parentesis\n");}
;

%%
int yylexerrs = 0;

void yyerror(const char *msg) {
    printf("linea #%d: %s\n", yylineno, msg);
    return;
}
