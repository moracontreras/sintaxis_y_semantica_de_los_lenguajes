#include "symbol.h"
#include <stdio.h>
#include <string.h>

#define MAX_SYMBOLS 100

static char symbols[MAX_SYMBOLS][50];
static int symbol_count = 0;

bool buscar(char *id) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbols[i], id) == 0) {
            return true;
        }
    }
    return false;
}

void colocar(char *id) {
    if (!buscar(id)) {
        strcpy(symbols[symbol_count++], id);
    }
}

bool definir(char *id) {
    if (buscar(id)) {
        return false;
    }
    colocar(id);
    return true;
}

bool verificar(char *id) {
    if (!buscar(id)) {
        return false;
    }
    return true;
}


