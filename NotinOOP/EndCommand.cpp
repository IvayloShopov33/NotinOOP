#include "EndCommand.h"
#include "Engine.h"

void EndCommand::execute(Engine& engine) {
    engine.stop();
    std::cout << "Exiting the system...\n";
}