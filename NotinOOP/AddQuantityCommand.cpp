#include "AddQuantityCommand.h"
#include "Engine.h"

AddQuantityCommand::AddQuantityCommand(const std::string& name, int quantity)
    : fragranceName(name), quantity(quantity) {
}

void AddQuantityCommand::execute(Engine& engine) {
    auto currentUser = engine.getSystem().getCurrentUser();

    if (!currentUser || !currentUser->isAdmin()) {
        std::cout << "Error: Access denied.\n";

        return;
    }

    engine.getSystem().addQuantityToFragrance(fragranceName, quantity);
}