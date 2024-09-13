#include "FacadeProduto.hpp"
#include "Observer.hpp"
#include "LimparTelaCommand.hpp"
#include "PausarTelaCommand.hpp"
#include "AguardarEntradaCommand.hpp"
#include "LimparEntradaCommand.hpp"
#include "ProdutoFactory.hpp"
#include "ProdutoKg.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

std::string obterDataEHoraAtual() {
    // Obter o tempo atual
    auto now = std::chrono::system_clock::now();
    std::time_t tempoAtual = std::chrono::system_clock::to_time_t(now);

    // Converter para o formato local de data e hora
    std::tm* now_tm = std::localtime(&tempoAtual);

    // Criar uma string formatada com a data e a hora
    std::ostringstream oss;
    oss << std::put_time(now_tm, "%d-%m-%Y %H:%M:%S");

    return oss.str();
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
            std::string nome, tipo;

            if (iss >> id >> std::ws && std::getline(iss, nome, ' ') && iss >> preco >> quantidade) {
                // Determina se é Produto ou ProdutoKg com base na string "tipo"
                if (nome.find("kg") != std::string::npos) {
                    produtos.push_back(new ProdutoKg(id, nome, preco, quantidade));
                } else {
                    produtos.push_back(new Produto(id, nome, preco, quantidade));
                }
            }
        }
        file.close();
    }
}

void FacadeProduto::saveProdutos() {
    std::ofstream file("produtos.txt");
    if (file.is_open()) {
        for (const auto& produto : produtos) {
            file << produto->getId() << " "
                 << produto->getNome() << " "
                 << produto->getPreco() << " "
                 << produto->getQuantidade() << std::endl;
        }
        file.close();
    }
}


void FacadeProduto::cadastrarProduto(const Produto& produto) {
    produtos.push_back(produto.clone());  // Adiciona o clone do produto
    saveProdutos();  // Salva a lista atualizada após adicionar o produto
    std::cout << "Produto adicionado com sucesso!\n";
}




bool FacadeProduto::existsProduto(int id) {
    return std::any_of(produtos.begin(), produtos.end(),
        [id](const Produto* p) { return p->getId() == id; });
}


bool FacadeProduto::existsNomeProduto(const std::string& nome) {
    return std::any_of(produtos.begin(), produtos.end(),
        [&nome](const Produto* p) { return p->getNome() == nome; });
}




void FacadeProduto::entradaMaterial(int id, int quantidadeAdicional) {
    for (auto& produto : produtos) {
        if (produto->getId() == id) {
            int novaQuantidade = produto->getQuantidade() + quantidadeAdicional;
            produto->setQuantidade(novaQuantidade);
            saveProdutos();
            std::cout << "Estoque atualizado. Novo estoque do produto: " << novaQuantidade << std::endl;
            return;
        }
    }
    std::cerr << "Produto não encontrado.\n";
}


Produto* FacadeProduto::buscarProduto(int id) {
    for (auto& produto : produtos) {
        if (produto->getId() == id) {
            return produto->clone();
        }
    }
    return nullptr;
}

void FacadeProduto::exibirEstoque() {
    for (const auto& produto : produtos) {
        std::cout << produto->toString() << std::endl;
    }
}


void FacadeProduto::vendaProduto() {
    std::string nome;
    int quantidadeVenda;
    float carrinho = 0.0;
    bool finalizar = false;
    PausarTelaCommand pausarTela(3);
    LimparTelaCommand limparTela;
    LimparEntradaCommand limparEntrada;

    while (!finalizar) {
        limparTela.execute();
        std::cout << "Total do carrinho: " << carrinho << "R$\n";
        std::cout << "Digite o nome do item a ser vendido, ou 'FIM' para finalizar a compra: ";
        std::getline(std::cin, nome);

        if (nome == "FIM") {
            finalizar = true;
        } else {
            Produto* produto = nullptr;
            for (auto& p : produtos) {
                if (p->getNome() == nome) {
                    produto = p;
                    break;
                    return;
                }
            }

            if (produto != nullptr) {
                std::cout << "Quantidade de " << produto->getNome() << " a ser vendida: ";
                std::cin >> quantidadeVenda;
                limparEntrada.execute();

                if (produto->getQuantidade() >= quantidadeVenda) {
                    float totalItem = quantidadeVenda * produto->getPreco();
                    carrinho += totalItem;
                    produto->setQuantidade(produto->getQuantidade() - quantidadeVenda);
                    saveProdutos();
                    std::cout << "Adicionado ao carrinho " << quantidadeVenda << " unidades de " << produto->getNome() << ".\n";
                    pausarTela.execute();
                } else {
                    std::cerr << "Quantidade insuficiente em estoque para " << produto->getNome() << ".\n";
                    pausarTela.execute();
                }
            } else {
                std::cerr << "Produto com nome " << nome << " não encontrado.\n";
                pausarTela.execute();
            }
        }
    }

    // Salvar o valor total da venda em vendas.txt
    std::string data = obterDataEHoraAtual();
    std::ofstream file("vendas.txt", std::ios::app);
    if (file.is_open()) {
        file << "Venda realizada em: " << data << " Valor:" << std::fixed << std::setprecision(2) << carrinho << "R$\n";
        file.close();
    }
    
    notifyObservers(carrinho); // Notifica os observers da venda
    std::cout << "Total da venda: " << std::fixed << std::setprecision(2) << carrinho << "R$\n";
}

Produto* FacadeProduto::buscarProdutoPorNome(const std::string& nome) {
    for (auto& produto : produtos) {
        if (produto->getNome() == nome) {
            return produto->clone();
        }
    }
    return nullptr;
}

void FacadeProduto::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void FacadeProduto::removeObserver(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void FacadeProduto::notifyObservers(float valorVenda) {
    for (auto& observer : observers) {
        observer->update(valorVenda);
    }
}

