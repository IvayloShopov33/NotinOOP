#pragma once
#include "Command.h"

class ViewCartCommand : public Command {
public:
    void execute(Engine& engine) override;
};