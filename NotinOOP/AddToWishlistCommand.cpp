#include "AddToWishlistCommand.h"
#include "BuyerActionVisitor.h"
#include "Buyer.h"
#include "Engine.h"

AddToWishlistCommand::AddToWishlistCommand(const std::string& name) : fragranceName(name) {}

void AddToWishlistCommand::execute(Engine& engine) {
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
        buyer.addToWishlist(frag);
        std::cout << "The perfume '" << fragranceName << "' was added to your wishlist.\n";
        });

    user->acceptModifier(visitor);

    if (!visitor.wasExecuted()) {
        std::cout << "Error! Only buyers have access to the wishlist.\n";
    }
}