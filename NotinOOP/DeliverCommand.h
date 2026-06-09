#pragma once
#include "Command.h"

class DeliverCommand : public Command {
private:
    int purchaseId;

public:
    DeliverCommand(int id);

    void execute(Engine& engine) override;
};