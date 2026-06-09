#include "AddToCartCommand.h"
#include "BuyerActionVisitor.h"
#include "Buyer.h"
#include "Engine.h"

AddToCartCommand::AddToCartCommand(const std::string& name) : fragranceName(name) {}

void AddToCartCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();
    if (!user) {
        std::cout << "Error! You must be logged in.\n";

        return;
    }

    auto frag = engine.getSystem().findFragranceByName(fragranceName);
    if (!frag) {
        std::cout << "Error! Perfume with name '" << fragranceName << "' was not found in the catalog.\n";

        return;
    }

    BuyerActionVisitor visitor([&frag, this](Buyer& buyer) {
        buyer.addToCart(frag);
        std::cout << "The perfume '" << fragranceName << "' was added to your cart.\n";
        });

    user->acceptModifier(visitor);

    if (!visitor.wasExecuted()) {
        std::cout << "Error! Only buyers have access to the cart.\n";
    }
}