#include <cstdio>
#include <algorithm>
#include <cstring>
#include "poli.hpp"

Polinomio::Polinomio(int grau) : grau(grau), termos(0) {
    if(grau < 0)
        throw std::invalid_argument("Grau do polinomio deve ser positivo");

    coeficientes = new int[grau + 1];
    memset(coeficientes, 0, (grau + 1) * sizeof(int));
}

Polinomio::~Polinomio() {
    delete[] coeficientes;
    coeficientes = nullptr;
}

Polinomio::Polinomio(const Polinomio &outro)
    : grau(outro.grau), termos(outro.termos)
{
    coeficientes = new int[grau + 1];
    memcpy(coeficientes, outro.coeficientes, (grau + 1) * sizeof(int));
}

Polinomio &Polinomio::operator=(const Polinomio &outro) {
    if(this == &outro)
        return *this;

    delete[] coeficientes;

    grau = outro.grau;
    termos = outro.termos;
    coeficientes = new int[grau + 1];
    memcpy(coeficientes, outro.coeficientes, (grau + 1) * sizeof(int));

    return *this;
}

int Polinomio::insTermo(int exp, int coef) {
    if(exp < 0 || exp > grau)
        return 0;

    if(coeficientes[exp] == 0 && coef != 0)
        termos++;
    else if(coeficientes[exp] != 0 && coef == 0)
        termos--;

    coeficientes[exp] = coef;
    return 1;
}

int Polinomio::getTermo(int exp, int &coef) const {
    if(exp < 0 || exp > grau)
        return 0;

    if(coeficientes[exp] == 0)
        return 0;

    coef = coeficientes[exp];
    return 1;
}

int Polinomio::calculaPx(int x) const {
    int resultado = 0;
    int potencia = 1;

    for(int i = 0; i <= grau; i++) {
        resultado += coeficientes[i] * potencia;
        potencia *= x;
    }

    return resultado;
}

Polinomio Polinomio::soma(const Polinomio &q) const {
    int maiorGrau = std::max(grau, q.grau);
    Polinomio resultado(maiorGrau);

    for(int i = 0; i <= maiorGrau; i++) {
        int coefP = (i <= grau) ? coeficientes[i] : 0;
        int coefQ = (i <= q.grau) ? q.coeficientes[i] : 0;
        int s = coefP + coefQ;

        if(s != 0)
            resultado.insTermo(i, s);
    }

    return resultado;
}

Polinomio Polinomio::mult(const Polinomio &q) const {
    Polinomio resultado(grau + q.grau);

    for(int i = 0; i <= grau; i++) {
        for(int j = 0; j <= q.grau; j++) {
            int produto = coeficientes[i] * q.coeficientes[j];
            int coefAtual = resultado.coeficientes[i + j];
            resultado.insTermo(i + j, coefAtual + produto);
        }
    }

    return resultado;
}

Polinomio Polinomio::div(const Polinomio& q) const {
    int grauResultado = grau - q.grau;

    if(grauResultado < 0)
        return Polinomio(0);

    int maiorGrau = std::max(grau, q.grau);

    int *dividendo = new int[maiorGrau + 1]();
    int *divisor = new int[maiorGrau + 1]();

    for(int i = 0; i <= grau; i++) dividendo[i] = coeficientes[i];
    for(int i = 0; i <= q.grau; i++) divisor[i] = q.coeficientes[i];

    int grauDivisor = maiorGrau;
    while(grauDivisor > 0 && divisor[grauDivisor] == 0)
        grauDivisor--;

    if(divisor[grauDivisor] == 0) {
        delete[] dividendo;
        delete[] divisor;
        throw std::domain_error("Divisao por polinomio zero");
    }

    Polinomio resultado(grauResultado);

    for(int i = maiorGrau; i >= grauDivisor; i--) {
        if(dividendo[i] == 0)
            continue;

        int quociente = dividendo[i] / divisor[grauDivisor];
        int expQuociente = i - grauDivisor;

        resultado.insTermo(expQuociente, quociente);

        for(int j = 0; j <= grauDivisor; j++)
            dividendo[expQuociente + j] -= quociente * divisor[j];
    }

    delete[] dividendo;
    delete[] divisor;

    return resultado;
}

Polinomio Polinomio::fromFile(const std::string &nome) {
    FILE *arquivo = fopen(nome.c_str(), "r");

    if(arquivo == nullptr)
        throw std::runtime_error("Erro ao abrir arquivo: " + nome);

    int grau;
    if(fscanf(arquivo, "%d", &grau) != 1 || grau < 0) {
        fclose(arquivo);
        throw std::runtime_error("Grau invalido no arquivo: " + nome);
    }

    Polinomio p(grau);

    for(int i = grau; i >= 0; i--) {
        int coef;
        if(fscanf(arquivo, "%d", &coef) != 1) {
            fclose(arquivo);
            throw std::runtime_error("Erro ao ler coeficiente de grau " + std::to_string(i) + " em " + nome);
        }
        p.insTermo(i, coef);
    }

    fclose(arquivo);
    return p;
}
