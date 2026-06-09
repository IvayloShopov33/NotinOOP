#include "DeliverCommand.h"
#include "Engine.h"

DeliverCommand::DeliverCommand(int id) : purchaseId(id) {}

void DeliverCommand::execute(Engine& engine) {
    auto currentUser = engine.getSystem().getCurrentUser();

    if (!currentUser || !currentUser->isAdmin()) {
        std::cout << "Error: Access denied.\n";

        return;
    }

    if (engine.getSystem().deliverPurchase(purchaseId)) {
        std::cout << "Purchase #" << purchaseId << " is now marked as DELIVERED.\n";
    }
    else {
        std::cout << "Error: Purchase with such ID not found or not in PENDING state.\n";
    }
}