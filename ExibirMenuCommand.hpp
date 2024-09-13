// ExibirMenuCommand.hpp
#ifndef EXIBIR_MENU_COMMAND_HPP
#define EXIBIR_MENU_COMMAND_HPP

#include "Command.hpp"
#include "ProdutoKg.hpp"
#include "FacadeProduto.hpp"
#include "CaixaObserver.hpp"
#include "LimparTelaCommand.hpp"
#include "PausarTelaCommand.hpp"
#include "AguardarEntradaCommand.hpp"
#include "LimparEntradaCommand.hpp"
#include <iostream>

class ExibirMenuCommand : public Command {
public:
    explicit ExibirMenuCommand(FacadeProduto& facade) : facade(facade) {}

    void execute() override {
        LimparTelaCommand limparTela;
        PausarTelaCommand pausarTela(3);
        LimparEntradaCommand limparEntrada;
        AguardarEntradaCommand aguardarEntrada;

        CaixaObserver caixaObserver;
        facade.addObserver(&caixaObserver);

        while (true) {
            limparTela.execute();
            std::cout << "Menu:\n";
            std::cout << "1. Cadastrar Produto\n";
            std::cout << "2. Entrada de Material\n";
            std::cout << "3. Registrar Venda\n";
            std::cout << "4. Exibir Dados\n";
            std::cout << "5. Sair e Salvar\n";
            std::cout << "Escolha uma opção: ";

            int opcao;
            std::cin >> opcao;
            limparEntrada.execute();

            switch (opcao) {
                case 1: {
                    int id;
                    std::string nome;
                    float preco;
                    int quantidade;
                    std::string tipo;

                    std::cout << "Digite o Id do produto: ";
                    std::cin >> id;
                    limparEntrada.execute();

                    if (facade.existsProduto(id)) {
                        std::cerr << "Produto com esse Id já existe!\n";
                        break;
                    }

                    std::cout << "Digite o Nome do produto: ";
                    std::getline(std::cin, nome);

                    if (facade.existsNomeProduto(nome)) {
                        std::cerr << "Produto com esse nome já existe!\n";
                        break;
                    }

                    std::cout << "Digite o Preço do produto: ";
                    std::cin >> preco;

                    std::cout << "Digite a Quantidade do produto no estoque: ";
                    std::cin >> quantidade;

                    std::cout << "O produto é unitário ou por quilograma? (unitario/kg): ";
                    std::cin >> tipo;
                    limparEntrada.execute();

                    Produto* produto;
                    if (tipo == "kg") {
                        produto = new ProdutoKg(id, nome, preco, quantidade);
                    } else {
                        produto = new Produto(id, nome, preco, quantidade);
                    }
                    facade.cadastrarProduto(*produto);
                    delete produto;  // Liberar a memória alocada
                    break;
                }
                case 2: {
                    int id, quantidadeAdicional;

                    std::cout << "Digite o Id do produto: ";
                    std::cin >> id;
                    limparEntrada.execute();

                    if (facade.buscarProduto(id) == nullptr) {
                        std::cerr << "Produto com esse Id não existe!\n";
                        break;
                    }

                    std::cout << "Digite a quantidade a ser adicionada ao estoque: ";
                    std::cin >> quantidadeAdicional;
                    limparEntrada.execute();

                    facade.entradaMaterial(id, quantidadeAdicional);
                    std::cout << "Estoque atualizado com sucesso!\n";
                    break;
                }
                case 3: {
                    limparTela.execute();
                    facade.vendaProduto();
                    pausarTela.execute();
                    break;
                }
                case 4: {
                    limparTela.execute();
                    facade.exibirEstoque();
                    aguardarEntrada.execute();
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

            pausarTela.execute();
        }
    }

private:
    FacadeProduto& facade;
};

#endif // EXIBIR_MENU_COMMAND_HPP
