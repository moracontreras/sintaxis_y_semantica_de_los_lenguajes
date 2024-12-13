
%{
#include "parser.h"
%}

%option header-file="scanner.h"  
%option outfile="scanner.c"     
%option yylineno                

Letra           [a-zA-Z]
Digito          [0-9]
LetraDigito     [a-zA-Z0-9]
Espacio         [ \t\n]
Asignacion      ":="
Comentario      "//".*      

%%

"programa"          { return PROGRAMA; }
"fin"               { return FIN; }
"entero"            { return ENTERO; }
"leer"              { return LEER; }
"escribir"          { return ESCRIBIR; }

{Letra}({LetraDigito})*         { yylval.str = strdup(yytext); return ID; }
{Digito}+                       { yylval.str = strdup(yytext); return CTE; }
{Asignacion}                    { return ASIGNACION; }

";"                             {return PUNTO_Y_COMA;}
","                             {return COMA;}
"("                             {return PAREN_IZQ;}
")"                             {return PAREN_DER;}
"+"                             {return MAS;}
"-"                             {return MENOS;}
"*"                             {return MULTIPLICACION;}
"/"                             {return DIVISION;}
"%"                             {return MODULO;}

{Comentario}                    ;
{Espacio}+                      ;

{Digito}+{LetraDigito}+                                                                               {yylexerrs++; printf("linea #%d: Error lexico: constante invalida: %s\n", yylineno, yytext);}
{Letra}{LetraDigito}*[^ \t\na-zA-Z0-9;,\%\(\)+\-\*/]+({LetraDigito}|[^ \t\na-zA-Z0-9;,\%\(\)+\-\*/])* {yylexerrs++; printf("linea #%d: Error lexico: identificador invalido: %s\n", yylineno, yytext);}
[^ \t\na-zA-Z0-9;,\%\(\)+\-\*\:\=/]+                                                                  {yylexerrs++; printf("linea #%d: Error lexico: cadena desconocida: %s\n", yylineno, yytext);}
[^ \t\na-zA-Z0-9;,\%\(\)+\-\*/]+                                                                      {yylexerrs++; printf("linea #%d: Error lexico: asignacion mal formada: %s\n", yylineno, yytext);}

%%

int yywrap(void) {
    return 1;
}
