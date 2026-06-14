#include "CreateAdminCommand.h"
#include "Engine.h"
#include <iostream>

CreateAdminCommand::CreateAdminCommand(const std::string& username, const std::string& password)
    : newUsername(username), newPassword(password) {
}

void CreateAdminCommand::execute(Engine& engine) {
    auto currentUser = engine.getSystem().getCurrentUser();

    if (!currentUser) {
        std::cout << "Error! You must be logged in to execute this command.\n";
        return;
    }

    if (!currentUser->isAdmin()) {
        std::cout << "Error! Only administrators can create new admin accounts.\n";
        return;
    }

    engine.getSystem().registerAdmin(newUsername, newPassword);
}