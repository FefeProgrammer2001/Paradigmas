#ifndef POLI_HPP
#define POLI_HPP

#include <string>
#include <stdexcept>

class Polinomio {
private:
    int *coeficientes;
    int grau;
    int termos;

public:
    explicit Polinomio(int grau);

    ~Polinomio();

    Polinomio(const Polinomio &outro);
    Polinomio &operator=(const Polinomio &outro);

    int getGrau() const { return grau; }
    int getTermos() const { return termos; }

    int insTermo(int exp, int coef);
    int getTermo(int exp, int &coef) const;

    int calculaPx(int x) const;

    Polinomio soma(const Polinomio &q) const;
    Polinomio mult(const Polinomio &q) const;
    Polinomio div(const Polinomio &q) const;

    Polinomio operator+(const Polinomio &q) const { return soma(q); }
    Polinomio operator*(const Polinomio &q) const { return mult(q); }
    Polinomio operator/(const Polinomio &q) const { return div(q); }

    static Polinomio fromFile(const std::string &nome);
};

#endif
