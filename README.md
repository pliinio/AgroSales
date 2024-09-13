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

- **`main.cpp`**: Contém a lógica do menu principal e interação com o usuário.
- **`Produto.cpp/hpp`**: Classe para criação e manipulação de produtos.
- **`FacadeProduto.cpp/hpp`**: Implementa o padrão Facade para centralizar o gerenciamento de produtos.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests.
