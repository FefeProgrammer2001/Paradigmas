public class Figura {
    private double comprimento;
    private double altura;

    public Figura() {
        this.comprimento = 0.0;
        this.altura = 0.0;
    }

    public double getComprimento() {
        return comprimento;
    }

    public double getAltura() {
        return altura;
    }

    public void setComprimento(double comprimento) {
        this.comprimento = comprimento;
    }

    public void setAltura(double altura) {
        this.altura = altura;
    }

    @Override
    public String toString() {
        return "Comprimento: " + getComprimento() + "\nAltura: " + getAltura();
    }
}