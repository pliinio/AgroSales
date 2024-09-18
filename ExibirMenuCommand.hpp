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
        setlocale(LC_ALL, "pt_BR.UTF-8");
        LimparTelaCommand limparTela;
        PausarTelaCommand pausarTela(3);
        LimparEntradaCommand limparEntrada;
        AguardarEntradaCommand aguardarEntrada;

        CaixaObserver caixaObserver;
        facade.addObserver(&caixaObserver);

        while (true) {
            limparTela.execute();
            std::cout << "MENU PRINCIPAL\n";
            std::cout << "+--------------------------------------+\n";
            std::cout << "| 1. CADASTRAR PRODUTO                 |\n";
            std::cout << "| 2. ENTRADA DE MATERIAL               |\n";
            std::cout << "| 3. REGISTRAR VENDA                   |\n";
            std::cout << "| 4. EXIBIR ESTOQUE                    |\n";
            std::cout << "| 5. EXIBIR SALDO EM CAIXA             |\n";
            std::cout << "| 6. EXIBIR VENDAS                     |\n";
            std::cout << "| 7. SAIR E SALVAR                     |\n";
            std::cout << "+--------------------------------------+\n";
            std::cout << "ESCOLHA UMA OPÇÃO: ";


            int opcao;
            std::cin >> opcao;
            limparEntrada.execute();

            switch (opcao) {
                case 1: {
                    setlocale(LC_ALL, "pt_BR.UTF-8");
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
                case 5:{
                    limparTela.execute();
                    facade.exibirSaldoCaixa();
                    break;
                }
                case 6:{
                    limparTela.execute();
                    facade.exibirVendas();
                    break;
                }
                case 7:
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
