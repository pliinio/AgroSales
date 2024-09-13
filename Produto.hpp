#ifndef PRODUTO_HPP
#define PRODUTO_HPP

#include <string>

class Produto {
public:
    Produto(int id, const std::string& nome, float preco, int quantidade);

    int getId() const;
    void setId(int id);

    std::string getNome() const;
    void setNome(const std::string& nome);

    float getPreco() const;
    void setPreco(float preco);

    int getQuantidade() const;
    void setQuantidade(int quantidade);

    std::string toString() const;

private:
    int id;
    std::string nome;
    float preco;
    int quantidade;
};

#endif // PRODUTO_HPP
