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

%type <str> prog exp 

%left MAS MENOS
%left MULTIPLICACION DIVISION MODULO
%precedence NEG

%%
todo	: prog {if (yynerrs || yylexerrs) YYABORT;}
prog: PROGRAMA ID {printf("programa: %s\n", $2);} l_sent FIN 
;

l_sent: sent
    | l_sent sent
;

sent:
    ENTERO ID PUNTO_Y_COMA {printf("Sentencia declaracion: %s\n", $2);}
    | ID ASIGNACION exp PUNTO_Y_COMA {printf("Sentencia asignacion\n");}
    | LEER PAREN_IZQ l_id PAREN_DER PUNTO_Y_COMA {printf("Sentencia leer\n");}
    | ESCRIBIR PAREN_IZQ l_exp PAREN_DER PUNTO_Y_COMA {printf("Sentencia escribir\n");}
    | error PUNTO_Y_COMA
;

l_id:
    ID
    | l_id COMA ID
;

l_exp:
    exp
    | l_exp COMA exp
;

exp: exp MAS exp { printf("suma\n"); }
    | exp MENOS exp { printf("resta\n"); }
    | exp MULTIPLICACION exp { printf("multiplicacion\n"); }
    | exp DIVISION exp { printf("division\n"); }
    | exp MODULO exp { printf("modulo\n"); }
    | MENOS exp %prec NEG { printf("inversion\n"); }
    | PAREN_IZQ {printf("abre parentesis\n");}  exp PAREN_DER {printf("cierra parentesis\n");}
    | CTE
    | ID
;

%%
int yylexerrs = 0;

void yyerror(const char *msg) {
    printf("linea #%d: %s\n", yylineno, msg);
    return;
}
