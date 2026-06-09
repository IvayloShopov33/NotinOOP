#pragma once
#include "Command.h"
#include <string>

class AddToWishlistCommand : public Command {
private:
    std::string fragranceName;

public:
    AddToWishlistCommand(const std::string& name);

    void execute(Engine& engine) override;
};