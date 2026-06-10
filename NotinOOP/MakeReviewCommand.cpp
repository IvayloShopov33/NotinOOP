#include <iostream>

#include "MakeReviewCommand.h"
#include "Engine.h"
#include "ReviewValidator.h"

MakeReviewCommand::MakeReviewCommand(const std::string& fragName, int rating, const std::string& comment)
    : fragranceName(fragName), rating(rating), comment(comment) {}

void MakeReviewCommand::execute(Engine& engine) {
    auto user = engine.getSystem().getCurrentUser();

    if (!user || user->isAdmin()) {
        std::cout << "Error! Only logged-in buyers can write reviews.\n";
        return;
    }

    try {
        ReviewValidator::validateRating(rating);
        ReviewValidator::validateComment(comment);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error! " << e.what() << "\n";
        return;
    }

    if (engine.getSystem().addReviewToFragrance(fragranceName, user->getId(), rating, comment)) {
        std::cout << "Thank you! Your review for '" << fragranceName << "' was published.\n";
    }
}