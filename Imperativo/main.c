#include <stdio.h>
#include "vetor.h"

#define N (1UL << 28) // 2^28 elementos

int main(void) {
    Vetor vetor;
    alocar(&vetor, N);
    inicializar(&vetor);
    imprimir(&vetor);
    desalocar(&vetor);
    printf("Soma realizada com sucesso...\n");
    return 0;
}