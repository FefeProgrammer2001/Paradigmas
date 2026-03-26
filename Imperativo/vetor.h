#include <stdio.h>

typedef struct {
    size_t *vetor;
    size_t n;
} Vetor;

void alocar(Vetor *vetor, size_t n);

void desalocar(Vetor *vetor);

void inicializar(Vetor *vetor);

size_t somar(Vetor *vetor);

void imprimir(Vetor *vetor);