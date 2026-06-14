#pragma once
#include "Command.h"
#include <string>

class CreateAdminCommand : public Command {
private:
    std::string newUsername;
    std::string newPassword;

public:
    CreateAdminCommand(const std::string& username, const std::string& password);
    void execute(Engine& engine) override;
};