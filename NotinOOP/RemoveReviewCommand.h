#pragma once
#include "Command.h"

class RemoveReviewCommand : public Command {
private:
    int fragranceId;
    int reviewId;

public:
    RemoveReviewCommand(int fragranceId, int reviewId);

    void execute(Engine& engine) override;
};