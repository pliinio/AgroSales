// LimparTelaCommand.hpp
#ifndef LIMPAR_TELA_COMMAND_HPP
#define LIMPAR_TELA_COMMAND_HPP

#include "Command.hpp"
#include <cstdlib>

class LimparTelaCommand : public Command {
public:
    void execute() override {
        #ifdef _WIN32
            system("cls"); // Windows
        #else
            (void)system("clear"); // Unix/Linux/MacOS
        #endif
    }
};

#endif // LIMPAR_TELA_COMMAND_HPP
