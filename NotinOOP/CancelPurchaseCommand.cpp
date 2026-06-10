#include <iostream>

#include "CancelPurchaseCommand.h"
#include "Engine.h"

CancelPurchaseCommand::CancelPurchaseCommand(int id) : purchaseId(id) {}

void CancelPurchaseCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();

    if (!user) {
        std::cout << "Error! You must be logged in to cancel an order.\n";

        return;
    }

    if (engine.getSystem().cancelPurchase(purchaseId)) {
        std::cout << "Order #" << purchaseId
            << " was successfully canceled. The money has been refunded to your balance.\n";
    }
}