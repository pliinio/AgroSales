#include "FacadeProduto.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

FacadeCadastro& FacadeCadastro::getInstance() {
    static FacadeCadastro instance;
    return instance;
}

void FacadeCadastro::loadProdutos() {
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

void FacadeCadastro::saveProdutos() {
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

bool FacadeCadastro::existsProduto(int id) {
    return std::any_of(produtos.begin(), produtos.end(),
                       [id](const Produto& p) { return p.getId() == id; });
}

void FacadeCadastro::cadastrarProduto(const Produto& produto) {
    if (!existsProduto(produto.getId())) {
        produtos.push_back(produto);
        saveProdutos(); // Salva a lista atualizada após adicionar o produto
    } else {
        std::cerr << "Produto já existe.\n";
    }
}

void FacadeCadastro::entradaMaterial(int id, int quantidadeAdicional) {
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


Produto* FacadeCadastro::buscarProduto(int id) {
    for (auto& produto : produtos) {
        if (produto.getId() == id) {
            return &produto;
        }
    }
    return nullptr;
}

void FacadeCadastro::exibirEstoque() {
    for (const auto& produto : produtos) {
        std::cout << produto.toString() << std::endl;
    }
}

bool FacadeCadastro::existsNomeProduto(const std::string& nome) {
    return std::any_of(produtos.begin(), produtos.end(),
                       [nome](const Produto& p) { return p.getNome() == nome; });
}

void FacadeCadastro::vendaProduto(int id, int quantidadeVenda) {
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
