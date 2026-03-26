public class Main {
    public static void main(String[] args) {
        Retangulo r1 = new Retangulo();

        r1.setAltura(10.5);
        r1.setComprimento(4.5);
        r1.setCor("Verde");

        System.out.println("Área da figura em cm quadrados: " + r1.calcularArea());
        System.out.println(r1);
    }
}
