#include <stdio.h>
#include <stdlib.h>
#include "tabla.h"

int main(int argc, char* argv[]){
    if (argc < 3) {
        fprintf(stderr, "En este archivo %s necesitas: <inicio> <fin> {incremento}\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    float inicio = atof(argv[1]);
    float fin = atof(argv[2]);
    float incremento = (argc > 3) ? atof(argv[3]) : 1;
    
    armar_tabla(inicio, fin, incremento);

    return 0;
}