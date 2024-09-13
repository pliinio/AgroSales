# Sistema de Gestão de Produtos: AgroSales

Este é um sistema simples de gestão de produtos, desenvolvido em C++, que permite adicionar, atualizar e vender produtos em um estoque. Utiliza padrões de design como Singleton e Facade para organizar o código de forma clara e eficiente.

## Funcionalidades

- **Cadastrar Produto**: Adicione produtos com ID, nome, preço e quantidade.
- **Entrada de Material**: Atualize o estoque com entrada de material.
- **Registrar Venda**: Registre vendas, reduza automaticamente o estoque e some o valor de cada venda no caixa. Por segurança cada venda é registrada com data e valor em 'vendas.txt'.
- **Exibir estoque**: Mostra os detalhes de cada produto de forma organizada.

## Padrões de Projeto Utilizados

- **Singleton**: Para garantir uma única instância de `FacadeProduto` em todo o sistema.
- **Facade**: Para simplificar a interação com os módulos de gerenciamento de produtos.
- **Observer**: Observa o método de venda e notifica o caixa a cada nova venda somando no seu valor atual.
- **Command**: Encapsula o funcionamento do menu principal.
- **Factory Method**: Permite a utilização de produtos por Quilograma
- **Strategy**: Permite a utilização do sistema de descontos
  
## Como Executar

1. Clone o repositório:
    ```bash
    git clone https://github.com/seu-usuario/AgroSales.git
    cd AgroSales
    ```
2. Compile o projeto:
    ```bash
    make
    ```
3. Execute o programa:
    ```bash
    ./main
    ```

## Estrutura do Código

- **`main.cpp`**: Apenas instancia uma Fachada para manipular os produtos e um Command para iniciar o menu.
- **`ProdutoFactory.hpp`**: Classe base para o padrão Factory Method.
- **`Produto.cpp/hpp`**: Classe para criação e manipulação de produtos.
- **`Produto.hpp`**: Subclasse de **`Produto.cpp/hpp`** que sobrescreve o método toString() para possibilitar a adição de produtos por Quilograma ao estoque.
- **`FacadeProduto.cpp/hpp`**: Implementa o padrão Facade para centralizar o gerenciamento de produtos.
- **`Command.hpp`**: Classe base para o padrão Command.
- **`ExibirMenuCommand.hpp`**, **`LimparEntradaCommand.hpp`**, **`LimparTelaCommand.hpp`**, **`PausarTelaCommand.hpp`**, **`AguardarEntradaCommand`**: Manipulações da interface do menu via padrão Command.
- **`Observer.hpp`**: Classe base para o padrão Observer.
- **`CaixaObserver`**: Subclasse implementadora do padrão Observer diretamente para o arquivo **`caixa.txt`**.
- **`DescontoStrategy`**: Classe base para o padrão Strategy.
- **`DescontoPercentual.hpp`**: Subclasse que implementa o desconto em percentual.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.
