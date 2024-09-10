#include "FacadeProduto.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <chrono>

void pausar(int segundos) {
    std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

void limparMenu() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        (void)system("clear"); // Unix/Linux/MacOS
    #endif
}

void limparBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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

void FacadeProduto::vendaProduto() {
    std::string nome;
    int quantidadeVenda;
    float carrinho = 0.0;
    bool finalizar = false;

    while (!finalizar) {
        limparMenu();
        std::cout << "Total do carrinho: " << carrinho << "R$\n";
        std::cout << "Digite o nome do item a ser vendido, ou 'FIM' para finalizar a compra: ";
        std::getline(std::cin, nome);

        if (nome == "FIM") {
            finalizar = true;
        } else {
            Produto* produto = nullptr;
            for (auto& p : produtos) {
                if (p.getNome() == nome) {
                    produto = &p;
                    break;
                    return;
                }
            }

            if (produto != nullptr) {
                std::cout << "Quantidade de " << produto->getNome() << " a ser vendida: ";
                std::cin >> quantidadeVenda;
                limparBuffer();

                if (produto->getQuantidade() >= quantidadeVenda) {
                    float totalItem = quantidadeVenda * produto->getPreco();
                    carrinho += totalItem;
                    produto->setQuantidade(produto->getQuantidade() - quantidadeVenda);
                    saveProdutos();
                    std::cout << "Adicionado ao carrinho " << quantidadeVenda << " unidades de " << produto->getNome() << " vendidas.\n";
                    pausar(3);
                } else {
                    std::cerr << "Quantidade insuficiente em estoque para " << produto->getNome() << ".\n";
                    pausar(3);
                }
            } else {
                std::cerr << "Produto com nome " << nome << " não encontrado.\n";
                pausar(3);
            }
        }
    }

    // Salvar o valor total da venda em vendas.txt
    std::ofstream file("vendas.txt", std::ios::app);
    if (file.is_open()) {
        file << "Venda total: " << std::fixed << std::setprecision(2) << carrinho << "R$\n";
        file.close();
    }

    std::cout << "Total da venda: " << std::fixed << std::setprecision(2) << carrinho << "R$\n";
    //pausar(3);
}

Produto* FacadeProduto::buscarProdutoPorNome(const std::string& nome) {
    for (auto& produto : produtos) {
        if (produto.getNome() == nome) {
            return &produto;
        }
    }
    return nullptr;
}
