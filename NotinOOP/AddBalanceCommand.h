#pragma once
#include "Command.h"

class AddBalanceCommand : public Command {
private:
    double amount;

public:
    AddBalanceCommand(double amount);

    void execute(Engine& engine) override;
};