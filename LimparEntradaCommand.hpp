// LimparEntradaCommand.hpp
#ifndef LIMPAR_ENTRADA_COMMAND_HPP
#define LIMPAR_ENTRADA_COMMAND_HPP

#include "Command.hpp"
#include <iostream>
#include <limits>

class LimparEntradaCommand : public Command {
public:
    void execute() override {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

#endif // LIMPAR_ENTRADA_COMMAND_HPP
