#ifndef DESCONTO_PERCENTUAL_HPP
#define DESCONTO_PERCENTUAL_HPP

#include "DescontoStrategy.hpp"

class DescontoPercentual : public DescontoStrategy {
public:
    explicit DescontoPercentual(float porcentagem) : porcentagem(porcentagem) {}

    float aplicarDesconto(float valor) const override {
        return valor * (1 - porcentagem / 100);
    }

private:
    float porcentagem;
};

#endif // DESCONTO_PERCENTUAL_HPP
