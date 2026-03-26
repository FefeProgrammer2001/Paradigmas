public class Circulo extends Figura {
    private final double pi;
    private String cor;

    public Circulo() {
        this.pi = 3.14159;
    }

    public double getRaio() { return raio; }
    public void setRaio(double raio) { this.raio = raio; }

    public double getPi() { return pi; }

    public double calcularAreaCirculo() {
        return getPi() * (getRaio() * getRaio());
    }

    @Override
    public String toString() {
        return super.toString() + "\nCor: " + getCor()
    }
}