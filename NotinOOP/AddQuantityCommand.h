#pragma once
#include "Command.h"

#include <string>

class AddQuantityCommand : public Command {
private:
    std::string fragranceName;
    int quantity;

public:
    AddQuantityCommand(const std::string& name, int quantity);

    void execute(Engine& engine) override;
};