#include "Euclidiano.hpp"
#include <iostream>
#include <stdexcept>

const double PontoEuclidiano::TOLERANCIA = 1e-10;
const int PontoEuclidiano::MAX_ITERACOES = 1000;

PontoEuclidiano::PontoEuclidiano() : Ponto2D() {}
PontoEuclidiano::PontoEuclidiano(double x, double y) : Ponto2D(x, y) {}
PontoEuclidiano::PontoEuclidiano(const Ponto2D& p) : Ponto2D(p.getX(), p.getY()) {}
PontoEuclidiano::PontoEuclidiano(const PontoEuclidiano& outro) : Ponto2D(outro) {}
PontoEuclidiano::~PontoEuclidiano() {}

double PontoEuclidiano::raizQuadrada(double valor) const {
    if(valor < 0.0)
        throw std::invalid_argument("Raiz quadrada nao pode ser menor que zero");
    if(valor == 0.0) return 0.0;

    double r = valor / 2.0;
    for(int i = 0; i < MAX_ITERACOES; ++i) {
        double r_novo = (r + valor / r) / 2.0;
        double diff = r_novo - r;
        if(diff < 0.0) diff = -diff;
        r = r_novo;
        if(diff < TOLERANCIA) break;
    }
    return r;
}

double PontoEuclidiano::distanciaEuclidiana(const Ponto2D& outro) const {
    double dx = outro.getX() - x;
    double dy = outro.getY() - y;
    return raizQuadrada(dx * dx + dy * dy);
}

void PontoEuclidiano::exibir() const {
    std::cout << "PontoEuclidiano(" << x << ", " << y << ")";
}