#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int temp_counter = 0;

void comenzar(char *programa) {
    printf("#include <stdio.h>\n\nint main(void) {\n");
}

void terminar(void) {
    printf("    return 0;\n}\n");
}

void declarar(char *id) {
    printf("    int %s;\n", id);
}

void asignar(char *vizq, char *vder) {
    printf("    %s = %s;\n", vizq, vder);
}

void leer_id(char *id) {
    printf("    scanf(\"%%d\", &%s);\n", id);
}

void escribir_exp(char *exp) {
    printf("    printf(\"%%d\\n\", %s);\n", exp);
}

char *gen_infijo(char *pizq, char op, char *pder) {
    char *ptemp = gen_temporal();
    declarar(ptemp);
    printf("    %s = %s %c %s;\n", ptemp, pizq, op, pder);
    return ptemp;
}

char *invertir(char *id) {
    char *ptemp = gen_temporal();
    declarar(ptemp);
    printf("    %s = -%s;\n", ptemp, id);
    return ptemp;
}

char *gen_temporal() {
    char *temp = malloc(20);
    sprintf(temp, "_Temp%d", ++temp_counter);
    return temp;
}
