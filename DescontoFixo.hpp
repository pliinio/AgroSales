#ifndef DESCONTO_FIXO_HPP
#define DESCONTO_FIXO_HPP

#include "DescontoStrategy.hpp"

class DescontoFixo : public DescontoStrategy {
public:
    explicit DescontoFixo(float valor) : valor(valor) {}

    float aplicarDesconto(float valorOriginal) const override {
        return valorOriginal - valor;
    }

private:
    float valor;
};

#endif // DESCONTO_FIXO_HPP
