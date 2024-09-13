#ifndef PRODUTO_FACTORY_HPP
#define PRODUTO_FACTORY_HPP

#include "Produto.hpp"
#include "ProdutoKg.hpp"
#include <memory>
#include <string>


class ProdutoFactory {
public:
    static std::unique_ptr<Produto> criarProduto(int id, const std::string& nome, float preco, int quantidade, bool porKg) {
        if (porKg) {
            return std::make_unique<ProdutoKg>(id, nome, preco, quantidade);
        } else {
            return std::make_unique<Produto>(id, nome, preco, quantidade);
        }
    }
};

#endif // PRODUTO_FACTORY_HPP
