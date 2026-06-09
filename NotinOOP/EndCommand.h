#pragma once
#include "Command.h"

class EndCommand : public Command
{
public:
	void execute(Engine& engine) override;
};