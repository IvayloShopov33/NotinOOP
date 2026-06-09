#pragma once
#include "Command.h"

class LogoutCommand : public Command {
public:
    void execute(Engine& engine) override;
};