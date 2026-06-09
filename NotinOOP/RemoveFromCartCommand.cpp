#include "RemoveFromCartCommand.h"
#include "BuyerActionVisitor.h"
#include "Buyer.h"
#include "Engine.h"

RemoveFromCartCommand::RemoveFromCartCommand(const std::string& name) : fragranceName(name) {}

void RemoveFromCartCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();
    if (!user) {
        std::cout << "Error! You must be logged in.\n";

        return;
    }

    auto frag = engine.getSystem().findFragranceByName(fragranceName);
    if (!frag) {
        std::cout << "Error! Perfume with name '" << fragranceName << "' does not exist.\n";

        return;
    }

    BuyerActionVisitor visitor([&frag, this](Buyer& buyer) {
        if (buyer.removeFromCart(frag->getId())) {
            std::cout << "The perfume '" << fragranceName << "' was removed from cart.\n";
        }
        else {
            std::cout << "Error! This perfume is not in your cart.\n";
        }
        });

    user->acceptModifier(visitor);

    if (!visitor.wasExecuted()) {
        std::cout << "Error! Only buyers have access to the cart.\n";
    }
}