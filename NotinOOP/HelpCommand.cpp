#include "HelpCommand.h"
#include "Engine.h"
#include "HelpVisitor.h"

void HelpCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();

    std::cout << "\n--- AVAILABLE COMMANDS ---\n";

    if (user == nullptr) {
        // If there is no logged in user (Guest)
        std::cout << "register <username> <password> - Register a new buyer account\n";
        std::cout << "login <username> <password>    - Log into your account\n";
    }
    else {
		// Visitor pattern to display commands based on user role (Buyer or Admin)
        HelpVisitor helpVisitor;
        user->accept(helpVisitor);

        // Logout command available to anyone logged in
        std::cout << "logout                                            - Log out of current session\n";
    }

    // Exit command always available
    std::cout << "end                                               - Save and exit application\n";
    std::cout << "---------------------------\n";
}