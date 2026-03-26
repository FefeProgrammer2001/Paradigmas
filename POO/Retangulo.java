public class Retangulo extends Figura {
    private String cor;

    public Retangulo() {
        this.cor = null;
    }

    public String getCor() {
        return cor;
    }

    public void setCor(String cor) {
        this.cor = cor;
    }

    public double calcularArea() {
        return getComprimento() * getAltura();
    }

    @Override
    public String toString() {
        return super.toString() + "\nCor: " + getCor();
    }
}
