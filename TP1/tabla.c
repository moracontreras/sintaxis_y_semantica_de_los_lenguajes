#include "tabla.h"

void armar_tabla(double inicio, double fin, double incremento){
    assert(incremento > 0 && inicio <= fin);

    printf("\tNudos\t|\tKm/h\n");
    printf("\t-----\t|\t------\n");
    for (double i = inicio; i <= fin; i += incremento) {
        float km_h = convertir_a_km(i);
        fprintf(stdout, "\t%.4g\t|\t%.6g\n", i, km_h);
    }
}