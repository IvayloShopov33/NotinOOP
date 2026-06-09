#include "LoginCommand.h"
#include "Engine.h"

LoginCommand::LoginCommand(const std::string& username, const std::string& password)
	: username(username), password(password) {}

void LoginCommand::execute(Engine& engine)
{
    if (engine.getSystem().loginUser(username, password)) {
        std::cout << "Successfully logged in!\n";
    }
    else {
        std::cout << "Login failed.\n";
    }
}