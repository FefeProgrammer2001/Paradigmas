#include <exception>
#include <iostream>
#include <stdexcept>
#include "poli.hpp"

void imprimirPolinomio(const Polinomio &p, const char *nome) {
    std::cout << nome << "(x) = ";

    bool primeiro = true;

    for(int exp = p.getGrau(); exp >= 0; exp--) {
        int coef = 0;

        if(p.getTermo(exp, coef)) {
            if(!primeiro) {
                if(coef > 0)
                    std::cout << " + ";
                else
                    std::cout << " - ";
            } else {
                if(coef < 0)
                    std::cout << "-";
            }

            int absCoef = coef < 0 ? -coef : coef;

            if(exp == 0) {
                std::cout << absCoef;
            } else {
                if(absCoef != 1)
                    std::cout << absCoef << "*";

                std::cout << "x";

                if(exp != 1)
                    std::cout << "^" << exp;
            }

            primeiro = false;
        }
    }

    if(primeiro)
        std::cout << "0";

    std::cout << '\n';
}

Polinomio lerPolinomio(const char *nome) {
    int grau;

    std::cout << "Digite o grau do polinomio " << nome << ": ";
    std::cin >> grau;

    while(grau < 0) {
        std::cout << "Grau invalido. Digite um grau >= 0: ";
        std::cin >> grau;
    }

    Polinomio p(grau);

    std::cout << "Digite os coeficientes de " << nome
              << " do maior grau ate o termo independente\n";

    for(int exp = grau; exp >= 0; exp--) {
        int coef;
        std::cout << "Coeficiente de x^" << exp << ": ";
        std::cin >> coef;
        p.insTermo(exp, coef);
    }

    return p;
}

void calcularValorEmX(const Polinomio &p, const Polinomio &q) {
    int x;

    std::cout << "\nDigite um valor inteiro para x: ";
    std::cin >> x;

    std::cout << "p(" << x << ") = " << p.calculaPx(x) << '\n';
    std::cout << "q(" << x << ") = " << q.calculaPx(x) << '\n';
}

int main() {
    try {
        std::cout << "=== Operacoes com Polinomios ===\n\n";

        Polinomio p = lerPolinomio("p");
        std::cout << '\n';
        Polinomio q = lerPolinomio("q");

        std::cout << "\n=== Polinomios informados ===\n";
        imprimirPolinomio(p, "p");
        imprimirPolinomio(q, "q");

        std::cout << "\nGrau de p: " << p.getGrau() << '\n';
        std::cout << "Termos validos de p: " << p.getTermos() << '\n';
        std::cout << "Grau de q: " << q.getGrau() << '\n';
        std::cout << "Termos validos de q: " << q.getTermos() << '\n';

        calcularValorEmX(p, q);

        std::cout << "\n=== Resultados das operacoes ===\n";

        Polinomio s = p + q;
        imprimirPolinomio(s, "p + q");

        Polinomio m = p * q;
        imprimirPolinomio(m, "p * q");

        try {
            Polinomio d = p / q;
            imprimirPolinomio(d, "p / q");
        } catch(const std::domain_error &e) {
            std::cout << "p / q: erro: " << e.what() << '\n';
        }
    } catch(const std::exception &e) {
        std::cerr << "Erro: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
