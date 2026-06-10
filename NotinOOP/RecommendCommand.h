#pragma once
#include "Command.h"

class RecommendCommand : public Command {
public:
    void execute(Engine& engine) override;
};