// PausarTelaCommand.hpp
#ifndef PAUSAR_TELA_COMMAND_HPP
#define PAUSAR_TELA_COMMAND_HPP

#include "Command.hpp"
#include <chrono>
#include <thread>

class PausarTelaCommand : public Command {
public:
    explicit PausarTelaCommand(int segundos) : segundos(segundos) {}

    void execute() override {
        std::this_thread::sleep_for(std::chrono::seconds(segundos));
    }

private:
    int segundos;
};

#endif // PAUSAR_TELA_COMMAND_HPP
