#include <stdlib.h>
#include <stdio.h>

#include "poli.h"

polinomio *poli_create(int grau) {
    if (grau < 0) return NULL;

    polinomio *p = malloc(sizeof(polinomio));
    if (p == NULL) return NULL;

    p->grau = grau;
    p->termos = 0;

    p->coeficientes = malloc((grau + 1) * sizeof(int));
    if (p->coeficientes == NULL) {
        free(p);
        return NULL;
    }

    // Inicializa todos coeficientes com 0
    for (int i = 0; i <= grau; i++) {
        p->coeficientes[i] = 0;
    }

    return p;
}

void poli_destroy(polinomio **p){
    if(p != NULL && *p != NULL) {
        free((*p)->coeficientes);
        free(*p);
        *p = NULL;
    }

    return;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    if (p == NULL || exp < 0 || exp > p->grau || coef == 0) {
        return 0;
    }

    if (p->coeficientes[exp] == 0) {
        p->termos++;
    }

    p->coeficientes[exp] = coef;

    return 1;
}

int poli_get_termo(polinomio *p, int exp, int *coef) {
    if (p == NULL || coef == NULL || exp < 0 || exp > p->grau) {
        return 0;
    }

    if (p->coeficientes[exp] == 0) {
        return 0;
    }

    *coef = p->coeficientes[exp];
    return 1;
}

int calcula_px(polinomio *p, int x){
    if (p == NULL) return 0;

    int resultado = 0;
    int potencia = 1; // x^0

    for (int i = 0; i <= p->grau; i++) {
        resultado += p->coeficientes[i] * potencia;
        potencia *= x;
    }

    return resultado;
}

polinomio * poli_soma(polinomio *p, polinomio *q) {
    if (p == NULL || q == NULL) return NULL;

    int grau_max = (p->grau > q->grau) ? p->grau : q->grau;

    polinomio *r = poli_create(grau_max);
    if (r == NULL) return NULL;

    for (int i = 0; i <= grau_max; i++) {
        int coef_p = (i <= p->grau) ? p->coeficientes[i] : 0;
        int coef_q = (i <= q->grau) ? q->coeficientes[i] : 0;

        int soma = coef_p + coef_q;

        if (soma != 0) {
            poli_ins_termo(r, i, soma);
        }
    }

    return r;
}

polinomio * poli_mult(polinomio *p, polinomio *q) {
    if (p == NULL || q == NULL) return NULL;

    int grau_result = p->grau + q->grau;

    polinomio *r = poli_create(grau_result);
    if (r == NULL) return NULL;

    for (int i = 0; i <= p->grau; i++) {
        if (p->coeficientes[i] == 0) continue;

        for (int j = 0; j <= q->grau; j++) {
            if (q->coeficientes[j] == 0) continue;

            int exp = i + j;
            int valor_atual = r->coeficientes[exp];
            int novo_valor = valor_atual + (p->coeficientes[i] * q->coeficientes[j]);

            if (novo_valor != 0) {
                poli_ins_termo(r, exp, novo_valor);
            } else {
                // caso vire 0, zera direto e ajusta termos
                if (valor_atual != 0) {
                    r->coeficientes[exp] = 0;
                    r->termos--;
                }
            }
        }
    }

    return r;
}

polinomio * poli_div(polinomio *p, polinomio *q) {
    if (p == NULL || q == NULL) return NULL;

    // não pode dividir por polinômio nulo
    if (q->termos == 0) return NULL;

    // grau do quociente
    if (p->grau < q->grau) {
        return poli_create(0); // quociente 0
    }

    polinomio *r = poli_create(p->grau); // resto (cópia de p)
    if (r == NULL) return NULL;

    // copia p em r
    for (int i = 0; i <= p->grau; i++) {
        if (p->coeficientes[i] != 0) {
            poli_ins_termo(r, i, p->coeficientes[i]);
        }
    }

    polinomio *quoc = poli_create(p->grau - q->grau);
    if (quoc == NULL) {
        poli_destroy(&r);
        return NULL;
    }

    while (r->termos > 0 && r->grau >= q->grau) {
        // acha maior grau de r
        int grau_r = r->grau;
        while (grau_r >= 0 && r->coeficientes[grau_r] == 0) {
            grau_r--;
        }

        if (grau_r < q->grau) break;

        // acha maior grau de q
        int grau_q = q->grau;
        while (grau_q >= 0 && q->coeficientes[grau_q] == 0) {
            grau_q--;
        }

        int coef = r->coeficientes[grau_r] / q->coeficientes[grau_q];
        int exp = grau_r - grau_q;

        poli_ins_termo(quoc, exp, coef);

        // subtrai (coef * q * x^exp) de r
        for (int i = 0; i <= grau_q; i++) {
            if (q->coeficientes[i] != 0) {
                int pos = i + exp;
                int novo = r->coeficientes[pos] - coef * q->coeficientes[i];

                if (novo != 0) {
                    poli_ins_termo(r, pos, novo);
                } else {
                    if (r->coeficientes[pos] != 0) {
                        r->coeficientes[pos] = 0;
                        r->termos--;
                    }
                }
            }
        }
    }

    poli_destroy(&r);
    return quoc;
}
