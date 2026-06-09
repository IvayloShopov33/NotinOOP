#include "ViewCartCommand.h"
#include "BuyerActionVisitor.h"
#include "Buyer.h"
#include "Engine.h"

void ViewCartCommand::execute(Engine& engine) {
	auto user = engine.getSystem().getCurrentUser();
	if (!user) {
		std::cout << "Error! You must be logged in.\n";

		return;
	}

	BuyerActionVisitor visitor([](Buyer& buyer) {
		const auto& cart = buyer.getCart();

		if (cart.empty()) {
			std::cout << "Your cart is currently empty.\n";

			return;
		}

		std::cout << "\n--- YOUR CART ---\n";
		double total = 0.0;

		for (const auto& weakFrag : cart) {
			auto frag = weakFrag.lock();

			if (!frag) {
				std::cout << "- Product is no longer available in the catalog.\n";
				continue;
			}

			std::cout << "- " << frag->getBrand() << " " << frag->getName()
				<< " | Price: " << frag->getPrice() << " euro\n";

			const auto& notes = frag->getfragranceFamily();
			if (!notes.empty()) {
				std::cout << "  Notes: ";
				for (size_t i = 0; i < notes.size(); ++i) {
					std::cout << notes[i];

					if (i < notes.size() - 1) {
						std::cout << ", ";
					}
				}

				std::cout << "\n";
			}

			total += frag->getPrice();
		}

		std::cout << "----------------------\n";
		std::cout << "Total: " << total << " euro\n\n";
		});

	user->acceptModifier(visitor);

	if (!visitor.wasExecuted()) {
		std::cout << "Error! Only buyers have a cart.\n";
	}
}