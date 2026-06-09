#pragma once
#include "Command.h"

#include <string>

class BlockUserCommand : public Command {
private:
    std::string targetUsername;

public:
    BlockUserCommand(const std::string& username);

    void execute(Engine& engine) override;
};