# Sistema de Gestão de Produtos: AgroSales

Este é um sistema simples de gestão de produtos, desenvolvido em C++, que permite adicionar, atualizar e vender produtos em um estoque. Utiliza padrões de design como Singleton e Facade para organizar o código de forma clara e eficiente.

## Funcionalidades

- **Cadastro de Produtos**: Adicione produtos com ID, nome, preço e quantidade.
- **Atualização de Estoque**: Atualize o estoque com entrada de material.
- **Venda de Produtos**: Registre vendas e reduza automaticamente o estoque.
- **Exibição de Produtos**: Mostra os detalhes de cada produto de forma organizada.

## Padrões de Projeto Utilizados

- **Singleton**: Para garantir uma única instância de `FacadeProduto` em todo o sistema.
- **Facade**: Para simplificar a interação com os módulos de gerenciamento de produtos.
  
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
