#include "FacadeProduto.hpp"
#include "Produto.hpp"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>  // Para system()

void limparTela() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/MacOS
    #endif
}

void pausarTela(int segundos) {
    std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

void limparEntrada() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void aguardarEntrada() {
    std::cout << "\nPressione Enter para voltar ao menu principal...";
    limparEntrada(); // Limpa qualquer entrada residual
    std::cin.get(); // Aguarda o usuário pressionar Enter
}

void exibirMenu(FacadeCadastro& facade, const std::string& filename) {
    bool loggedIn = false;

    while (!loggedIn) {
        // Menu de login
    }

    while (true) {
        limparTela();
        std::cout << "Menu:\n";
        std::cout << "1. Adicionar Produto\n";
        std::cout << "2. Atualizar Estoque\n";
        std::cout << "3. Vender Produto\n";
        std::cout << "4. Exibir Dados\n";
        std::cout << "5. Sair e Salvar\n";
        std::cout << "Escolha uma opcao: ";

        int opcao;
        std::cin >> opcao;
        limparEntrada();

        switch (opcao) {
            case 1: {
                int id;
                std::string nome;
                float preco;
                int quantidade;

                std::cout << "Digite o Id do produto: ";
                std::cin >> id;
                limparEntrada();

                if (facade.buscarProduto(id) != nullptr) {
                    std::cerr << "Produto com esse Id já existe!\n";
                    break;
                }

                std::cout << "Digite o Nome do produto: ";
                std::getline(std::cin, nome);

                std::cout << "Digite o Preço do produto: ";
                std::cin >> preco;

                std::cout << "Digite a Quantidade do produto: ";
                std::cin >> quantidade;

                Produto produto(id, nome, preco, quantidade);
                facade.cadastrarProduto(produto);
                std::cout << "Produto adicionado com sucesso!\n";
                break;
            }
            case 2: {
                int id, quantidadeAdicional;

                std::cout << "Digite o Id do produto: ";
                std::cin >> id;
                limparEntrada();

                if (facade.buscarProduto(id) == nullptr) {
                    std::cerr << "Produto com esse Id não existe!\n";
                    break;
                }

                std::cout << "Digite a quantidade a ser adicionada ao estoque: ";
                std::cin >> quantidadeAdicional;
                limparEntrada();

                facade.entradaMaterial(id, quantidadeAdicional);
                std::cout << "Estoque atualizado com sucesso!\n";
                break;
            }
            case 3: {
                int id, quantidadeVenda;

                std::cout << "Digite o Id do produto: ";
                std::cin >> id;
                limparEntrada();

                Produto* produto = facade.buscarProduto(id);
                if (produto == nullptr) {
                    std::cerr << "Produto com esse Id não existe!\n";
                    break;
                }

                std::cout << "Quantidade de " << produto->getNome() << " a ser vendida: ";
                std::cin >> quantidadeVenda;
                limparEntrada();

                facade.vendaProduto(id, quantidadeVenda);
                break;
            }
            case 4: {
                limparTela();
                facade.exibirEstoque();
                aguardarEntrada();
                break;
            }
            case 5:
                facade.saveProdutos();
                std::cout << "Dados salvos. Saindo...\n";
                return;
            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
        }

        pausarTela(3);
    }
}


int main() {
    FacadeCadastro& facade = FacadeCadastro::getInstance();
    facade.loadProdutos();

    exibirMenu(facade, "produtos.txt");

    return 0;
}
