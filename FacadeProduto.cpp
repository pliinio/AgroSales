#include "FacadeProduto.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

FacadeProduto& FacadeProduto::getInstance() {
    static FacadeProduto instance;
    return instance;
}

void FacadeProduto::loadProdutos() {
    std::ifstream file("produtos.txt");
    if (file.is_open()) {
        produtos.clear(); // Limpa a lista antes de carregar novos dados
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int id, quantidade;
            float preco;
            std::string nome;
            if (iss >> id >> std::ws && std::getline(iss, nome, ' ') && iss >> preco >> quantidade) {
                produtos.emplace_back(id, nome, preco, quantidade);
            }
        }
        file.close();
    }
}

void FacadeProduto::saveProdutos() {
    std::ofstream file("produtos.txt");
    if (file.is_open()) {
        for (const auto& produto : produtos) {
            file << produto.getId() << " "
                 << produto.getNome() << " "
                 << produto.getPreco() << " "
                 << produto.getQuantidade() << std::endl;
        }
        file.close();
    }
}

void FacadeProduto::cadastrarProduto(const Produto& produto) {
    if (existsProduto(produto.getId())) {
        std::cerr << "Produto com esse ID já existe!\n";
        return;  // Impede continuação
    }

    if (existsNomeProduto(produto.getNome())) {
        std::cerr << "Produto com esse nome já existe!\n";
        return;  // Impede continuação
    }

    produtos.push_back(produto);
    saveProdutos();  // Salva a lista atualizada após adicionar o produto
    std::cout << "Produto adicionado com sucesso!\n";
}

bool FacadeProduto::existsProduto(int id) {
    return std::any_of(produtos.begin(), produtos.end(),
                       [id](const Produto& p) { return p.getId() == id; });
}

bool FacadeProduto::existsNomeProduto(const std::string& nome) {
    return std::any_of(produtos.begin(), produtos.end(),
                       [nome](const Produto& p) { return p.getNome() == nome; });
}



void FacadeProduto::entradaMaterial(int id, int quantidadeAdicional) {
    for (auto& produto : produtos) {
        if (produto.getId() == id) {
            int novaQuantidade = produto.getQuantidade() + quantidadeAdicional;
            produto.setQuantidade(novaQuantidade);
            saveProdutos();
            std::cout << "Estoque atualizado. Novo estoque do produto: " << novaQuantidade << std::endl;
            return;
        }
    }
    std::cerr << "Produto não encontrado.\n";
}


Produto* FacadeProduto::buscarProduto(int id) {
    for (auto& produto : produtos) {
        if (produto.getId() == id) {
            return &produto;
        }
    }
    return nullptr;
}

void FacadeProduto::exibirEstoque() {
    for (const auto& produto : produtos) {
        std::cout << produto.toString() << std::endl;
    }
}

void FacadeProduto::vendaProduto(int id, int quantidadeVenda) {
    for (auto& produto : produtos) {
        if (produto.getId() == id) {
            if (produto.getQuantidade() >= quantidadeVenda) {
                produto.setQuantidade(produto.getQuantidade() - quantidadeVenda);
                saveProdutos();
                std::cout << "Venda realizada com sucesso! Estoque atualizado.\n";
            } else {
                std::cerr << "Quantidade insuficiente em estoque para realizar a venda.\n";
            }
            return;
        }
    }
    std::cerr << "Produto não encontrado.\n";
}
