#ifndef VENDA_PRODUTO_TEMPLATE_HPP
#define VENDA_PRODUTO_TEMPLATE_HPP

#include "Produto.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <sstream>

class VendaProdutoTemplate {
public:
    void venderProdutos() {
        limparTela();
        iniciarVenda();
        while (!finalizarVenda) {
            mostrarCarrinho();
            obterNomeProduto();
            if (nomeProduto == "FIM") {
                finalizarVenda = true;
            } else {
                buscarProdutoPorNome();
                if (produto) {
                    obterQuantidadeVenda();
                    processarVenda();
                } else {
                    produtoNaoEncontrado();
                }
            }
        }
        salvarVenda();
        finalizarProcesso();
    }

protected:
    virtual void limparTela() = 0;
    virtual void iniciarVenda() = 0;
    virtual void mostrarCarrinho() = 0;
    virtual void obterNomeProduto() = 0;
    virtual void buscarProdutoPorNome() = 0;
    virtual void obterQuantidadeVenda() = 0;
    virtual void processarVenda() = 0;
    virtual void produtoNaoEncontrado() = 0;
    virtual void salvarVenda() = 0;
    virtual void finalizarProcesso() = 0;

    Produto* produto = nullptr;
    std::string nomeProduto;
    int quantidadeVenda;
    float carrinho = 0.0;
    bool finalizarVenda = false;
};

#endif // VENDA_PRODUTO_TEMPLATE_HPP
