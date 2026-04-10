#include <iostream>
#include <iomanip>
#include <limits>
#include "Vetor.hpp"

#define TESTE_SUITE(nome) \
    std::cout << "\n===================================\n"; \
    std::cout << "  SUITE: " << (nome) << "\n"; \
    std::cout << "===================================\n";

#define TESTE_CASO(descricao, condicao) \
    do { \
        bool _ok = (condicao); \
        std::cout << "  [" << (_ok ? "PASS" : "FAIL") << "] " \
                           << (descricao) << "\n"; \
        if(!_ok) \
            std::cout << "       ^ FALHOU em " << __FILE__ \
                      << ":" << __LINE__ << "\n"; \
    } while(0)

#define TESTE_LANCA_EXCECAO(descricao, tipo_excecao, bloco) \
    do { \
        bool _lancou = false; \
        try { bloco; } \
        catch(const tipo_excecao&) { _lancou = true; } \
        catch(...) {} \
        std::cout << "  [" << (_lancou ? "PASS" : "FAIL") << "] " \
                  << (descricao) << "\n"; \
    } while(0)

#define TESTE_DOUBLE(descricao, obtido, esperado, tolerancia) \
    do { \
        double _diff = (obtido) - (esperado); \
        if(_diff < 0.0) _diff = -_diff; \
        bool _ok = (_diff <= (tolerancia)); \
        std::cout << "  [" << (_ok ? "PASS" : "FAIL") << "] " \
                  << (descricao) \
                  << " (obtido=" << std::fixed << std::setprecision(6) \
                  << (obtido) << ", esperado=" << (esperado) << ")\n"; \
    } while(0)

#define EXECUTAR_TESTES() executarTodosTestes()

void executarTodosTestes() {
    std::cout << "\n";
    std::cout << "###########################################\n";
    std::cout << "#      EXECUTANDO BATERIA DE TESTES       #\n";
    std::cout << "###########################################\n";

    TESTE_SUITE("Alocacao e Capacidade");
    {
        VetorPontos* v = new VetorPontos(5);

        TESTE_CASO("Capacidade inicial = 5", v->getCapacidade() == 5);
        TESTE_CASO("Quantidade inicial = 0", v->getQuantidade() == 0);
        TESTE_CASO("Posicao 0 vazia (nullptr)", v->getPonto(0) == nullptr);
        TESTE_CASO("Posicao 4 vezia (nullptr)", v->getPonto(4) == nullptr);

        delete v;
        TESTE_CASO("delete executado sem crash", true);
    }

    TESTE_SUITE("Insercao Simples e Getters");
    {
        VetorPontos* v = new VetorPontos(4);

        v->inserir(0, 0.0, 0.0);
        v->inserir(1, 3.0, 4.0);
        v->inserir(3, 7.0, 7.0);

        TESTE_CASO("Quantidade apos 3 insercoes = 3", v->getQuantidade() == 3);
        TESTE_CASO("Posicao 2 continua vazia",        v->getPonto(2) == nullptr);

        const PontoEuclidiano* p0 = v->getPonto(0);
        TESTE_CASO("P0.x == 0.0", p0 && p0->getX() == 0.0);
        TESTE_CASO("P0.y == 0.0", p0 && p0->getY() == 0.0);

        const PontoEuclidiano* p1 = v->getPonto(1);
        TESTE_CASO("P1.x == 3.0", p1 && p1->getX() == 3.0);
        TESTE_CASO("P1.y == 4.0", p1 && p1->getY() == 4.0);

        delete v;
    }

    TESTE_SUITE("Shift ao Inserir em Posicao Ocupada");
    {
        VetorPontos* v = new VetorPontos(3);

        v->inserir(0, 1.0, 1.0);
        v->inserir(1, 2.0, 2.0);
        v->inserir(2, 3.0, 3.0);

        v->inserir(1, 9.0, 9.0);

        TESTE_CASO("Capacidade expandiu para 4",       v->getCapacidade() == 4);
        TESTE_CASO("Quantidade = 4",                   v->getQuantidade() == 4);

        const PontoEuclidiano* p0 = v->getPonto(0);
        const PontoEuclidiano* p1 = v->getPonto(1);
        const PontoEuclidiano* p2 = v->getPonto(2);
        const PontoEuclidiano* p3 = v->getPonto(3);

        TESTE_CASO("Pos 0 continua (1,1)",     p0 && p0->getX()==1.0 && p0->getY()==1.0);
        TESTE_CASO("Pos 1 agora e (9,9)",      p1 && p1->getX()==9.0 && p1->getY()==9.0);
        TESTE_CASO("Pos 2 shiftada para (2,2)",p2 && p2->getX()==2.0 && p2->getY()==2.0);
        TESTE_CASO("Pos 3 shiftada para (3,3)",p3 && p3->getX()==3.0 && p3->getY()==3.0);

        delete v;
    }

    TESTE_SUITE("Remocao de Pontos");
    {
        VetorPontos* v = new VetorPontos(3);

        v->inserir(0, 5.0, 5.0);
        v->inserir(2, 8.0, 8.0);

        v->remover(0);
        TESTE_CASO("Apos remover pos 0, ela e nullptr", v->getPonto(0) == nullptr);
        TESTE_CASO("Quantidade diminuiu para 1",         v->getQuantidade() == 1);

        v->remover(2);
        TESTE_CASO("Apos remover pos 2, ela e nullptr", v->getPonto(2) == nullptr);
        TESTE_CASO("Quantidade diminuiu para 0",         v->getQuantidade() == 0);

        delete v;
    }

    TESTE_SUITE("Excecoes por Indice Invalido");
    {
        VetorPontos* v = new VetorPontos(3);  // índices válidos: 0, 1, 2

        TESTE_LANCA_EXCECAO(
            "inserir(-1) lanca IndiceInvalidoException",
            IndiceInvalidoException,
            v->inserir(-1, 0.0, 0.0)
        );
        TESTE_LANCA_EXCECAO(
            "inserir(3) lanca IndiceInvalidoException",
            IndiceInvalidoException,
            v->inserir(3, 0.0, 0.0)
        );
        TESTE_LANCA_EXCECAO(
            "remover(99) lanca IndiceInvalidoException",
            IndiceInvalidoException,
            v->remover(99)
        );
        TESTE_LANCA_EXCECAO(
            "getPonto(-1) lanca IndiceInvalidoException",
            IndiceInvalidoException,
            v->getPonto(-1)
        );
        TESTE_LANCA_EXCECAO(
            "distancia em vetor vazio lanca runtime_error",
            std::runtime_error,
            v->distancia(0, 1)
        );

        delete v;
    }
}

int main() {
    EXECUTAR_TESTES();
    return 0;
}