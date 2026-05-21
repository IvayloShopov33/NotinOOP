#pragma once
#include "Command.h"
#include <iostream>

class LoginCommand : public Command {
private:
    std::string username;
    std::string password;

public:
    LoginCommand(const std::string& username, const std::string& password);

    void execute(Engine& engine) override;
};