#ifndef EUCLIDIANO_HPP
#define EUCLIDIANO_HPP

#include "Ponto2D.hpp"

class PontoEuclidiano : public Ponto2D {
private:
    static const double TOLERANCIA;
    static const int MAX_ITERACOES;

public:
    PontoEuclidiano();
    PontoEuclidiano(double x, double y);
    PontoEuclidiano(const Ponto2D& ponto);
    PontoEuclidiano(const PontoEuclidiano& outro);
    ~PontoEuclidiano() override;

    double raizQuadrada(double valor) const;
    double distanciaEuclidiana(const Ponto2D& outro) const;

    void exibir() const override;
};

#endif