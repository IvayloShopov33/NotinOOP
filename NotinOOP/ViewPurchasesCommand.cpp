#include "ViewPurchasesCommand.h"
#include "Engine.h"

void ViewPurchasesCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();

    if (!user || user->isAdmin()) {
        std::cout << "Error! Only buyers have a shopping list.\n";

        return;
    }

    engine.getSystem().showCurrentUserPurchaseHistory(std::cout);
}