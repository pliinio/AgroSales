#ifndef DESCONTO_STRATEGY_HPP
#define DESCONTO_STRATEGY_HPP

class DescontoStrategy {
public:
    virtual float aplicarDesconto(float valor) const = 0;
    virtual ~DescontoStrategy() = default;
};

#endif // DESCONTO_STRATEGY_HPP
