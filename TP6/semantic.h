#ifndef SEMANTIC_H
#define SEMANTIC_H

void comenzar(char *programa);       
void terminar(void);                 
void asignar(char *vizq, char *vder); 
void leer_id(char *ids);             
void declarar(char *identificador);
void escribir_exp(char *exps);       
char *gen_infijo(char *pizq, char op, char *pder); 
char *invertir(char *id);           
char *gen_temporal(void);           

#endif