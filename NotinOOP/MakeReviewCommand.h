#pragma once
#include "Command.h"
#include <string>

class MakeReviewCommand : public Command {
private:
    std::string fragranceName;
    int rating;
    std::string comment;

public:
    MakeReviewCommand(const std::string& fragName, int rating, const std::string& comment);

    void execute(Engine& engine) override;
};