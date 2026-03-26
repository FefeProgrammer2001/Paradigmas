#include <stdio.h>
#include <stdlib.h>
#include "vetor.h"

void alocar(Vetor *vetor, size_t n) {
    vetor->n = n;
    vetor->vetor = (size_t*)malloc(n * sizeof(size_t));
    if(!vetor->vetor) {
        fprintf(stderr, "Erro ao alocar vetor\nLinha %d, Arquivo %s, na funcao %s\n", __LINE__, __FILE__, __func__);
        exit(EXIT_FAILURE);
    }
}

void desalocar(Vetor *vetor) {
    free(vetor->vetor);
}

void inicializar(Vetor *vetor) {
    for(size_t i = 0; i < vetor->n; i++) {
        vetor->vetor[i] = 1;
    }
}

size_t somar(Vetor *vetor) {
    size_t soma = 0;
    for(size_t i = 0; i < vetor->n; i++) {
        soma += vetor->vetor[i];
    }
    return soma;
}

void imprimir(Vetor *vetor) {
    size_t resultado = somar(vetor);
    printf("Resultado da soma: %zu\n", resultado);
}