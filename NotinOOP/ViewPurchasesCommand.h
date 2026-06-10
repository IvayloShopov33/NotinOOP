#pragma once
#include "Command.h"

class ViewPurchasesCommand : public Command {
public:
    void execute(Engine& engine) override;
};