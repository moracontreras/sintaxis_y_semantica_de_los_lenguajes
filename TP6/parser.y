%{
#include "scanner.h"
#include "symbol.h"
#include "semantic.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
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
           // No se necesita nada más aquí porque leer_id ya fue llamado
        }
        | ESCRIBIR PAREN_IZQ l_exp PAREN_DER PUNTO_Y_COMA {
              // No se necesita
          }
        | ID PUNTO_Y_COMA {
              if (!verificar($1)) {
                  yysemerrs++;
                  printf("linea #%d: Error semantico: identificador %s NO declarado\n", yylineno, $1);
              }
        }
        | error PUNTO_Y_COMA
;

l_id : ID {
           leer_id($1); // Llama a leer_id directamente
           free($1);    // Libera la memoria si strdup se usa en otro lugar
       }
     | l_id COMA ID {
           leer_id($3); // Llama a leer_id para el nuevo ID
           free($3);    // Libera la memoria del ID actual
       }
     ;


exp : exp MAS exp { 
          $$ = gen_infijo($1, '+', $3); 
      }
    | exp MENOS exp { 
          $$ = gen_infijo($1, '-', $3); 
      }
    | exp MULTIPLICACION exp { 
          $$ = gen_infijo($1, '*', $3); 
      }
    | exp DIVISION exp { 
          $$ = gen_infijo($1, '/', $3); 
      }
    | exp MODULO exp { 
          $$ = gen_infijo($1, '%', $3); 
      }
    | MENOS exp %prec NEG { 
          $$ = invertir($2); 
      }
    | PAREN_IZQ exp PAREN_DER { 
          $$ = $2; 
      }
    | CTE { 
          $$ = $1; 
      }
    | ID { 
          if (!verificar($1)) { 
              yysemerrs++; 
              printf("linea #%d: Error semantico: identificador %s NO declarado\n", yylineno, $1);
          } else $$ = $1 ;
      }
;

l_exp : exp {
            escribir_exp($1);  // Escribimos la expresión solo si es válida
        }
      | l_exp COMA exp {
                escribir_exp($3);  // Escribimos la expresión solo si es válida
        }
;
%%

int yylexerrs = 0;
int yysemerrs = 0;

void yyerror(const char *msg) {
    fprintf(stderr, "linea #%d: %s\n", yylineno, msg);
}