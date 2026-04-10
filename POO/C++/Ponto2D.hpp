#ifndef PONTO2D_HPP
#define PONTO2D_HPP

class Ponto2D {
protected:
    double x;
    double y;

public:
    Ponto2D();
    Ponto2D(double x, double y);
    Ponto2D(const Ponto2D& outro);
    virtual ~Ponto2D();

    double getX() const;
    double getY() const;
    void setX(double x);
    void setY(double y);

    virtual void exibir() const;
};

#endif