#include "RegisterCommand.h"
#include "Engine.h"

RegisterCommand::RegisterCommand(const std::string& username, const std::string& password)
    : username(username), password(password) {
}

void RegisterCommand::execute(Engine& engine) {
    engine.getSystem().registerUser(username, password);
}