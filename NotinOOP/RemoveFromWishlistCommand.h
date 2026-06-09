#pragma once
#include "Command.h"
#include <string>

class RemoveFromWishlistCommand : public Command {
private:
    std::string fragranceName;

public:
    RemoveFromWishlistCommand(const std::string& name);

    void execute(Engine& engine) override;
};