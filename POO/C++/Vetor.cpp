#include "Vetor.hpp"
#include <iostream>
#include <iomanip>

IndiceInvalidoException::IndiceInvalidoException(int indice, int capacidade)
    : std::out_of_range(
        "Indice " + std::to_string(indice) + 
        " invalido. Capacidade atual: " + std::to_string(capacidade) +
        " (indices validos: 0 a " + std::to_string(capacidade - 1) + ").")
{}

VetorPontos::VetorPontos(int cap) : capacidade(cap), quantidade(0) {
    dados = new PontoEuclidiano*[capacidade];
    for(int i = 0; i < capacidade; ++i)
        dados[i] = nullptr;
}

VetorPontos::~VetorPontos() {
    for(int i = 0; i < capacidade; ++i)
        delete dados[i];
    delete[] dados;
}

void VetorPontos::expandir(int indice) {
    int novaCapacidade = capacidade + 1;
    PontoEuclidiano **novoArray = new PontoEuclidiano*[novaCapacidade];

    for(int i = 0; i < indice; ++i)
        novoArray[i] = dados[i];

    novoArray[indice] = nullptr;

    for(int i = indice; i < capacidade; ++i)
        novoArray[i + 1] = dados[i];

    delete[] dados;
    dados = novoArray;
    capacidade = novaCapacidade;
}

void VetorPontos::inserir(int indice, double x, double y) {
    if(indice < 0 || indice >= capacidade)
        throw IndiceInvalidoException(indice, capacidade);

    if(dados[indice] != nullptr) {
        std::cout << "  [INFO] Posicao " << indice
                  << " ocupada. Elementos deslocados uma posicao a direita\n";
        expandir(indice);
    }

    dados[indice] = new PontoEuclidiano(x, y);
    ++quantidade;
}

void VetorPontos::remover(int indice) {
    if(indice < 0 || indice >= capacidade)
        throw IndiceInvalidoException(indice, capacidade);

    if(dados[indice] == nullptr) {
        std::cout << "  [AVISO] Posicao " << indice << " ja esta vazia\n";
        return;
    }

    delete dados[indice];
    dados[indice] = nullptr;
    --quantidade;
}

double VetorPontos::distancia(int i, int j) const {
    if(i < 0 || i >= capacidade) throw IndiceInvalidoException(i, capacidade);
    if(j < 0 || j >= capacidade) throw IndiceInvalidoException(j, capacidade);
    if(!dados[i]) throw std::runtime_error("Posicao " + std::to_string(i) + " esta vazia");
    if(!dados[j]) throw std::runtime_error("Posicao " + std::to_string(j) + "esta vazia");
    return dados[i]->distanciaEuclidiana(*dados[j]);
}

int VetorPontos::getCapacidade() const { return capacidade; }
int VetorPontos::getQuantidade() const { return quantidade; }

const PontoEuclidiano* VetorPontos::getPonto(int indice) const {
    if(indice < 0 || indice >= capacidade)
        throw IndiceInvalidoException(indice, capacidade);
    return dados[indice];
}

void VetorPontos::exibirTodos() const {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n+-------+-----------------------------+\n";
    std::cout << "| Indice| Ponto                       |\n";
    std::cout << "+-------+-----------------------------+\n";
    for (int i = 0; i < capacidade; ++i) {
        std::cout << "|  " << std::setw(4) << i << " | ";
        if (dados[i]) {
            dados[i]->exibir();
            std::cout << "|\n";
        } else {
            std::cout << "(vazio)                      |\n";
        }
    }
    std::cout << "+-------+-----------------------------+\n";
    std::cout << "  Quantidade inserida: " << quantidade
              << " / Capacidade: " << capacidade << "\n\n";
}