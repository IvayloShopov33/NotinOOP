#include "LogoutCommand.h"
#include "Engine.h"

void LogoutCommand::execute(Engine& engine) {
    engine.getSystem().logoutUser();
}