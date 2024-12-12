%{
#include "scanner.h"
#include "symbol.h"
#include "semantic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
%}
%code provides {
void yyerror(const char *msg);
extern int yylexerrs;
extern int yysemerrs;
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

%type <str> prog l_id l_exp sent exp

%left MAS MENOS
%left MULTIPLICACION DIVISION MODULO
%precedence NEG

%%
todo    : prog { if (yynerrs || yylexerrs || yysemerrs) YYABORT; }
;

prog    : PROGRAMA ID { comenzar($2); }
          l_sent FIN { terminar(); }
;

l_sent  : sent
        | l_sent sent
;

sent    : ENTERO ID PUNTO_Y_COMA {
              if (!definir($2)) { 
                  yysemerrs++; 
                  printf("linea #%d: Error semantico: identificador %s ya declarado\n", yylineno, $2); 
              } else {
                  declarar($2);
              }
          }
        | ID ASIGNACION exp PUNTO_Y_COMA {
              if (!verificar($1)) {
                  yysemerrs++;
                  printf("linea #%d: Error semantico: identificador %s NO declarado\n", yylineno, $1);
              } else {
                  asignar($1, $3);
              }
          }
        | LEER PAREN_IZQ l_id PAREN_DER PUNTO_Y_COMA {
              leer_id($3);
          }
        | ESCRIBIR PAREN_IZQ l_exp PAREN_DER PUNTO_Y_COMA {
              escribir_exp($3);
          }
        | error PUNTO_Y_COMA

;

l_id : ID { $$ = strdup($1); }
     | l_id COMA ID { 
         $$ = malloc(strlen($1) + strlen($3) + 3); 
         if (!$$) {
             fprintf(stderr, "Error: Memoria insuficiente.\n");
             exit(EXIT_FAILURE);
         }
         sprintf($$, "%s, %s", $1, $3); 
         free($1);
         free($3);
     }
;

l_exp : exp { $$ = strdup($1); }
      | l_exp COMA exp {
          $$ = malloc(strlen($1) + strlen($3) + 3);
          if (!$$) {
              fprintf(stderr, "Error: Memoria insuficiente.\n");
              exit(EXIT_FAILURE);
          }
          sprintf($$, "%s, %s", $1, $3);
          free($1);
          free($3);
      }
;

exp     : exp MAS exp { $$ = gen_infijo($1, '+', $3); }
        | exp MENOS exp { $$ = gen_infijo($1, '-', $3); }
        | exp MULTIPLICACION exp { $$ = gen_infijo($1, '*', $3); }
        | exp DIVISION exp { $$ = gen_infijo($1, '/', $3); }
        | exp MODULO exp { $$ = gen_infijo($1, '%', $3); }
        | MENOS exp %prec NEG { $$ = invertir($2); }
        | PAREN_IZQ exp PAREN_DER { $$ = $2; }
        | CTE { $$ = $1; }
        | ID { 
              if (!verificar($1)) { 
                  yysemerrs++; 
                  printf("linea #%d: Error semantico: identificador %s NO declarado\n", yylineno, $1); 
              } 
              $$ = $1; 
          }
;

%%

int yylexerrs = 0;
int yysemerrs = 0;

void yyerror(const char *msg) {
    fprintf(stderr, "linea #%d: %s\n", yylineno, msg);
}
