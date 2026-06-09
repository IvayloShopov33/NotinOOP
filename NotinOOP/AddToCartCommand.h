#pragma once
#include "Command.h"
#include <string>

class AddToCartCommand : public Command {
private:
    std::string fragranceName;

public:
    AddToCartCommand(const std::string& name);

    void execute(Engine& engine) override;
};