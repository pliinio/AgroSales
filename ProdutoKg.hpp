#ifndef PRODUTO_KG_HPP
#define PRODUTO_KG_HPP

#include "Produto.hpp"
#include <string>
#include <sstream>
#include <iomanip>

class ProdutoKg : public Produto {
public:
    ProdutoKg(int id, const std::string& nome, float preco, int quantidade)
        : Produto(id, nome, preco, quantidade) {}

    std::string toString() const override {
        std::stringstream ss;
        ss << "Id: " << getId()
           << " Produto: " << getNome()
           << " Preço Kg: " << std::fixed << std::setprecision(2) << getPreco() << "R$"
           << " Em estoque: " << getQuantidade();
        return ss.str();
    }

    Produto* clone() const override {
        return new ProdutoKg(*this);
    }
};

#endif // PRODUTO_KG_HPP
