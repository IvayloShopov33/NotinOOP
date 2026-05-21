#pragma once
#include <string>
#include <vector>

class Engine; // Pre-declaration to avoid circular dependencies

class Command {
public:
    virtual ~Command() = default;

    virtual void execute(Engine& engine) = 0;
};