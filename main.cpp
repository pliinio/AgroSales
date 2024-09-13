#include "FacadeProduto.hpp"
#include "ExibirMenuCommand.hpp"

int main() {
    FacadeProduto& facade = FacadeProduto::getInstance();
    facade.loadProdutos();

    ExibirMenuCommand menuCommand(facade);
    menuCommand.execute();

    return 0;
}
