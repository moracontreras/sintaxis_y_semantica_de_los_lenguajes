#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include <stdlib.h>
#include <stdio.h>

void programa() ;
void parser();
void lista_declaraciones() ;
void lista_identificadores() ;
void lista_sentencias() ;
void sentencia();
void expresion();
void termino();
void factor() ;
void lista_expresiones();
void error_sintactico_token();


#endif //PARSER_H
