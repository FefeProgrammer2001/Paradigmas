#include "Ponto2D.hpp"
#include <iostream>

Ponto2D::Ponto2D() : x(0.0), y(0.0) {}
Ponto2D::Ponto2D(double x, double y) : x(x), y(y) {}
Ponto2D::Ponto2D(const Ponto2D& outro) : x(outro.x), y(outro.y) {}
Ponto2D::~Ponto2D() {}

double Ponto2D::getX() const { return x; }
double Ponto2D::getY() const { return y; }
void Ponto2D::setX(double x) { this->x = x; }
void Ponto2D::setY(double y) { this->y = y; }

void Ponto2D::exibir() const {
    std::cout << "Ponto2D(" << x << ", " << y << ")";
}