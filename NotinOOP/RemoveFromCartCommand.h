#pragma once
#include "Command.h"
#include <string>

class RemoveFromCartCommand : public Command {
private:
    std::string fragranceName;

public:
    RemoveFromCartCommand(const std::string& name);

    void execute(Engine& engine) override;
};

