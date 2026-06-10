#include "RecommendCommand.h"
#include "Engine.h"

void RecommendCommand::execute(Engine& engine) {
    engine.getSystem().recommendFragrances();
}