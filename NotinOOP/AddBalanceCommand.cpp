#include <iomanip> // std::setprecision, std::fixed

#include "AddBalanceCommand.h"
#include "Engine.h"
#include "BuyerActionVisitor.h"
#include "Buyer.h"

AddBalanceCommand::AddBalanceCommand(double amount) : amount(amount) {}

void AddBalanceCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();
    if (!user) {
        std::cout << "Error! You must be logged in.\n";

        return;
    }

    if (amount <= 0) {
        std::cout << "Error! Invalid amount.\n";

        return;
    }

    // Creating the Visitor with the logic for adding balance
    BuyerActionVisitor visitor([this](Buyer& buyer) {
        buyer.addToBalance(amount);
        std::cout << "You have successfully added " << std::fixed << std::setprecision(2) << amount << " to your account. Current balance: "
            << std::fixed << std::setprecision(2) << buyer.getBalance() << " euro\n";
        });

    user->acceptModifier(visitor);

    if (!visitor.wasExecuted()) {
        std::cout << "Error! Only buyers can add funds to their account.\n";
    }
}