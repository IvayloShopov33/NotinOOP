#include "BlockUserCommand.h"
#include "Engine.h"

BlockUserCommand::BlockUserCommand(const std::string& username) : targetUsername(username) {}

void BlockUserCommand::execute(Engine& engine) {
    auto currentUser = engine.getSystem().getCurrentUser();

    if (!currentUser || !currentUser->isAdmin()) {
        std::cout << "Error: Only administrators can use this command!\n";

        return;
    }

    if (engine.getSystem().blockUser(targetUsername)) {
        std::cout << "User '" << targetUsername << "' has been successfully blocked and removed.\n";
    }
    else {
        std::cout << "Error: User '" << targetUsername << "' not found.\n";
    }
}