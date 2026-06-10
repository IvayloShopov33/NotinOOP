#pragma once
#include "Command.h"

class ViewBoughtCommand : public Command {
public:
    void execute(Engine& engine) override;
};