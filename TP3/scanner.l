%{
#include "tokens.h"

#define YYSTYPE char*
%}

%option noyywrap

Letra           [a-zA-Z]
Digito          [0-9]
LetraDigito     [a-zA-Z0-9]
Espacio         [ \t\n]
Asignacion      ":="
Comentario      "//".*

%%

"programa"                      {return PROGRAMA;}
"leer"                          {return LEER;}
"escribir"                      {return ESCRIBIR;}
"entero"                        {return ENTERO;}
"fin"                           {return FIN;}

{Letra}({LetraDigito})*         { yytext; return IDENTIFICADOR; }
{Digito}+                       { yytext; return CONSTANTE; }
{Asignacion}                    {return ASIGNACION;}

";"                             {return ';';}
","                             {return ',';}
"("                             {return '(';}
")"                             {return ')';}
"+"                             {return '+';}
"-"                             {return '-';}
"*"                             {return '*';}
"/"                             {return '/';}

{Comentario}                    ;
{Espacio}+                      ;

{Digito}+{LetraDigito}+                                                                                  { printf("Error lexico: constante invalida: %s\n",     yytext); }
{Letra}{LetraDigito}*[^ \t\na-zA-Z0-9;,:=\(\)\+\-\*/]+({LetraDigito}|[^ \t\na-zA-Z0-9;,:=\(\)\+\-\*/])*  { printf("Error lexico: identificador invalido: %s\n", yytext); }
[^ \t\na-zA-Z0-9;,:=\(\)\+\-\*/]+                                                                        { printf("Error lexico: cadena desconocida: %s\n",     yytext); }
([:=])+                                                                                                  { printf("Error lexico: asignacion mal formada: %s\n", yytext); }                                                                              

%%