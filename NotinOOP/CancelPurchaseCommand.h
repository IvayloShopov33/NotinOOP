#pragma once
#include "Command.h"

class CancelPurchaseCommand : public Command {
private:
    int purchaseId;
public:
    CancelPurchaseCommand(int id);
    void execute(Engine& engine) override;
};