#ifndef CAIXA_OBSERVER_HPP
#define CAIXA_OBSERVER_HPP

#include "Observer.hpp"
#include <fstream>
#include <iostream>

class CaixaObserver : public Observer {
private:
    float totalCaixa; // Valor total em caixa

    // Função para carregar o valor atual do caixa a partir do arquivo
    float carregarCaixa() {
        std::ifstream caixaFile("caixa.txt");
        float valorAtual = 0.0f; // Valor inicial padrão caso o arquivo não exista
        if (caixaFile.is_open()) {
            caixaFile >> valorAtual; // Lê o valor do caixa do arquivo (primeira linha)
            caixaFile.close();
        } 
        return valorAtual;
    }

    // Atualiza o arquivo caixa.txt com o valor total atualizado
    void atualizarCaixa(float novoValor) {
        std::ofstream caixaFile("caixa.txt", std::ios::trunc); // Abre o arquivo no modo de sobrescrita
        if (caixaFile.is_open()) {
            caixaFile << novoValor; // Grava o valor total atualizado no arquivo
            caixaFile.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo caixa.txt\n";
        }
    }

public:
    CaixaObserver() {
        totalCaixa = carregarCaixa(); // Inicializa o valor do caixa ao iniciar o observer
    }

    // Este método será chamado sempre que uma venda ocorrer
    void update(float valorVenda) override {
        totalCaixa = carregarCaixa();   // Garante que estamos com o valor atualizado do arquivo
        totalCaixa += valorVenda;       // Atualiza o total do caixa com a nova venda
        atualizarCaixa(totalCaixa);     // Salva o novo valor no arquivo
    }
};

#endif // CAIXA_OBSERVER_HPP
