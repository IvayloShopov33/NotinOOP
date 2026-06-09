#pragma once
#include "Command.h"
#include <string>

class RegisterCommand : public Command {
private:
    std::string username;
    std::string password;

public:
    RegisterCommand(const std::string& username, const std::string& password);
    void execute(Engine& engine) override;
};