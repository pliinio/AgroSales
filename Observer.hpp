// Observer.hpp
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

class Observer {
public:
    virtual void update(float valorVenda) = 0;  // Método que será chamado para atualizar o caixa
    virtual ~Observer() = default;
};

#endif // OBSERVER_HPP
