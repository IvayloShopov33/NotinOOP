#pragma once
#include "Command.h"

#include <string>
#include <vector>

class CreateFragranceCommand : public Command {
private:
    std::string name;
    std::string brand;
    double price;
    std::vector<std::string> familyNotes;

public:
    CreateFragranceCommand(const std::string& name, const std::string& brand, double price, const std::vector<std::string>& notes);

    void execute(Engine& engine) override;
};