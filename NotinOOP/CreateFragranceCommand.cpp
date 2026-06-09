#include "CreateFragranceCommand.h"
#include "Engine.h"

CreateFragranceCommand::CreateFragranceCommand(const std::string& name, const std::string& brand,
    double price, const std::vector<std::string>& notes)
    : name(name), brand(brand), price(price), familyNotes(notes) {
}

void CreateFragranceCommand::execute(Engine& engine) {
    auto currentUser = engine.getSystem().getCurrentUser();

    if (!currentUser || !currentUser->isAdmin()) {
        std::cout << "Error: Access denied.\n";
        return;
    }

    // Creating the perfume with a starting quantity of 0
    auto newFrag = std::make_shared<Fragrance>(name, brand, price, familyNotes, 0);
    engine.getSystem().addFragranceToCatalog(std::move(newFrag));

    std::cout << "Fragrance '" << name << "' was successfully added to the catalog!\n";
}