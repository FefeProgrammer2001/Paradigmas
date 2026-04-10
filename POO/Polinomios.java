// Classe para operação com polinômios

public class Polinomios {
    private double[] coeficientes;
    private int grau;
    private int qtdTermos;
    
    public Polinomios() {
        this.coeficientes = null;
        this.grau = 0;
        this.qtdTermos = 0;
    }

    private double potencia(double base, int exp) {
        if(exp == 0) return 1.0;
        double resultado = 1.0;
        int expAbs = Math.abs(exp);
        for(int i = 0; i < expAbs; i++) {
            resultado *= base;
        }
        return (exp < 0) ? 1.0 / resultado : resultado;
    }

    private int max(int a, int b) {
        return(a >= b) ? a : b;
    }

    private double abs(double a) {
        if(Double.isNaN(a)) return Double.NaN;
        return (a < 0.0 || (1.0 / a == Double.NEGATIVE_INFINITY)) ? -a : a;
    }

    public void inicializar(int qtdTermos, double[] coefs) {
        this.qtdTermos = qtdTermos;
        this.coeficientes = new double[qtdTermos];
        for(int i = 0; i < qtdTermos; i++) {
            this.coeficientes[i] = coefs[i];
        }
        this.grau = qtdTermos - 1;
    }

    public double calcular(int grau, int qtdTermos, double x) {
        double resultado = 0.0;
        for(int i = 0; i < qtdTermos; i++) {
            resultado += coeficientes[i] * potencia(x, grau - 1);
        }
        return resultado;
    }

    public void exibir() {
        StringBuilder sb = new StringBuilder();
        for(int i = 0; i < qtdTermos; i++) {
            int exp = grau - i;
            double coef = coeficientes[i];
            if(coef == 0) continue;

            if(sb.length() > 0 && coef > 0) sb.append(" + ");
            else if(coef < 0) sb.append(" - ");

            double absCoef = abs(coef);
            if(exp == 0) {
                sb.append(absCoef);
            } else if(exp == 1) {
                sb.append(absCoef).append("x");
            } else {
                sb.append(absCoef).append("x^").append(exp);
            }
        }
        System.out.println(sb.toString().isEmpty() ? "0" : sb.toString());
    }

    public Polinomios somar(Polinomios outro) {
        int maxTermos = max(this.qtdTermos, outro.qtdTermos);

        double[] coefs = new double[maxTermos];

        for(int i = 0; i < maxTermos; i++) {
            double a = (i < this.qtdTermos) ? this.coeficientes[this.qtdTermos - 1 - i] : 0;
            double b = (i < outro.qtdTermos) ? outro.coeficientes[outro.qtdTermos - 1 - i] : 0;
            coefs[maxTermos - 1 - i] = a + b;
        }

        Polinomios auxiliar = new Polinomios();
        auxiliar.inicializar(maxTermos, coefs);
        return auxiliar;
    }

    public Polinomios multiplicar(Polinomios outro) {
        int novoGrau = this.grau + outro.grau;
        int novoQtd = novoGrau + 1;
        double[] coefs = new double[novoQtd];

        for(int i = 0; i < this.qtdTermos; i++) {
            for(int j = 0; j < outro.qtdTermos; j++) {
                coefs[i + j] += this.coeficientes[i] * outro.coeficientes[j];
            }
        }

        Polinomios auxiliar = new Polinomios();
        auxiliar.inicializar(novoQtd, coefs);
        return auxiliar;
    }

    public Polinomios dividir(Polinomios divisor) {
        if(divisor.grau > this.grau) {
            System.out.println("Grau do divisor maior que o do dividendo");
            return new Polinomios();
        }

        int qtdQuociente = this.grau - divisor.grau + 1;
        double[] quocienteCoefs = new double[qtdQuociente];

        double[] auxiliarCoefs = new double[this.qtdTermos];
        for(int i = 0; i < this.qtdTermos; i++) {
            auxiliarCoefs[i] = this.coeficientes[i];
        }

        for(int i = 0; i < qtdQuociente; i++) {
            double fator = auxiliarCoefs[i] / divisor.coeficientes[0];
            quocienteCoefs[i] = fator;

            for(int j = 0; j < divisor.qtdTermos; j++) {
                auxiliarCoefs[i + j] -= fator * divisor.coeficientes[j];
            }
        }

        Polinomios auxiliar = new Polinomios();
        auxiliar.inicializar(qtdQuociente, quocienteCoefs);
        return auxiliar;
    }

    public int getGrau() { return grau; }
    public int getQtdTermos() { return qtdTermos; }
    public double[] getCoeficientes() { return coeficientes; }
}
