#ifndef FACADEPRODUTO_HPP
#define FACADEPRODUTO_HPP

#include "Produto.hpp"
#include "Observer.hpp"
#include "CaixaObserver.hpp"
#include <algorithm>
#include <vector>
#include <string>

class FacadeProduto {
public:
    static FacadeProduto& getInstance();

    void loadProdutos();  
    void saveProdutos();  

    void cadastrarProduto(const Produto& produto);
    void entradaMaterial(int id, int quantidadeAdicional);
    Produto* buscarProduto(int id);
    void exibirEstoque();
    bool existsNomeProduto(const std::string& nome);
    bool existsProduto(int id);
    void vendaProduto(void);
    Produto* buscarProdutoPorNome(const std::string& nome);
    void exibirSaldoCaixa();

    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void exibirVendas();


private:
    FacadeProduto() { loadProdutos(); }
    std::vector<Produto*> produtos;
    std::vector<Observer*> observers;

    void notifyObservers(float valorVenda);
    
};

#endif
