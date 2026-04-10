#ifndef VETOR_HPP
#define VETOR_HPP

#include "Euclidiano.hpp"
#include <stdexcept>

class IndiceInvalidoException : public std::out_of_range {
public:
    explicit IndiceInvalidoException(int indice, int capacidade);
};

class VetorPontos {
private:
    PontoEuclidiano **dados;
    int capacidade;
    int quantidade;

    void expandir(int indice);

public:
    explicit VetorPontos(int capacidade);
    ~VetorPontos();

    void inserir(int indice, double x, double y);

    void remover(int indice);

    double distancia(int i, int j) const;

    int getCapacidade() const;
    int getQuantidade() const;
    const PontoEuclidiano* getPonto(int indice) const;

    void exibirTodos() const;
};

#endif