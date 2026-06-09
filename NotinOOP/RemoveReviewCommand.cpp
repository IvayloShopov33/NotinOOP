#include "RemoveReviewCommand.h"
#include "Engine.h"

RemoveReviewCommand::RemoveReviewCommand(int fragranceId, int reviewId) 
    : fragranceId(fragranceId), reviewId(reviewId) {}

void RemoveReviewCommand::execute(Engine& engine) {
    auto currentUser = engine.getSystem().getCurrentUser();

    if (!currentUser || !currentUser->isAdmin()) {
        std::cout << "Error: Access denied.\n";

        return;
    }

    if (engine.getSystem().removeReviewAndPenalize(fragranceId, reviewId)) {
        std::cout << "Review successfully deleted.\n";
    }
    else {
        std::cout << "Error: Unsuccessful review deletion.\n";
    }
}