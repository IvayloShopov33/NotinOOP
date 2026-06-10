#include "CheckoutCommand.h"
#include "Engine.h"

void CheckoutCommand::execute(Engine& engine) {
    engine.getSystem().checkout();
}