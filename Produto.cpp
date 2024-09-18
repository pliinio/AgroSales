#include "Produto.hpp"
#include <sstream>
#include <iomanip>

Produto::Produto(int id, const std::string& nome, float preco, int quantidade)
    : id(id), nome(nome), preco(preco), quantidade(quantidade) {}

int Produto::getId() const { return id; }
void Produto::setId(int id) { this->id = id; }

std::string Produto::getNome() const { return nome; }
void Produto::setNome(const std::string& nome){ 
	setlocale(LC_ALL, "pt_BR.UTF-8");
	this->nome = nome; 
	}

float Produto::getPreco() const { return preco; }
void Produto::setPreco(float preco) { this->preco = preco; }

int Produto::getQuantidade() const { return quantidade; }
void Produto::setQuantidade(int quantidade) { this->quantidade = quantidade; }

std::string Produto::toString() const {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    std::stringstream ss;
    ss << "Id: " << id
       << " Produto: " << nome
       << " Preço unidade: " << std::fixed << std::setprecision(2) << preco << "R$"
       << " Em estoque: " << quantidade;
    return ss.str();
}

Produto* Produto::clone() const {
    return new Produto(*this);
}
