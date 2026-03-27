#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio * poli_create(int grau){
    polinomio *p = (polinomio*)malloc(sizeof(polinomio));
    if(p == NULL) {
        return NULL;
    }
    p->grau = grau;
    p->termos = 0;
    *p->coeficientes = (int*)malloc(grau + 1 * sizeof(int));
    if(p->coeficientes == NULL) {
        printf("Erro ao alocar vetor de polinomios. Linha %d no arquivo %s\n", __LINE__, __FILE__);
        free(p);
    }
   
    return p;
}

void poli_destroy(polinomio **p){
    // TODO: Implemente aqui a solucao para operacao destroy


    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente

    return 0;
}

int poli_get_termo(polinomio *p, int exp, int *coef){
    // TODO: Implemente aqui a solucao para operacao get coeficiente

    return 0;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)     
    
    return 0;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro

    return NULL;
}


