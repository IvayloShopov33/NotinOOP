#include "LoginCommand.h"

LoginCommand::LoginCommand(const std::string& username, const std::string& password)
	: username(username), password(password) {}

void LoginCommand::execute(Engine& engine)
{
	// TODO: Implement login logic using the engine
}