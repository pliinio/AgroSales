#ifndef FACADEPRODUTO_HPP
#define FACADEPRODUTO_HPP

#include "Produto.hpp"
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



private:
    FacadeProduto() { loadProdutos(); }
    std::vector<Produto> produtos;
    
};

#endif 
