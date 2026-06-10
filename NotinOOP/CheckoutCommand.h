#pragma once
#include "Command.h"

class CheckoutCommand : public Command {
public:
    void execute(Engine& engine) override;
};