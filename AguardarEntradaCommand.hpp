// AguardarEntradaCommand.hpp
#ifndef AGUARDAR_ENTRADA_COMMAND_HPP
#define AGUARDAR_ENTRADA_COMMAND_HPP

#include "Command.hpp"
#include <iostream>

class AguardarEntradaCommand : public Command {
public:
    void execute() override {
        std::cout << "\nPressione Enter para voltar ao menu principal...";
        std::cin.get();
    }
};

#endif // AGUARDAR_ENTRADA_COMMAND_HPP
