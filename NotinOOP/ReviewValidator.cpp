#include "ReviewValidator.h"
#include <stdexcept>

void ReviewValidator::validateRating(int rating) {
    if (rating < 0 || rating > 5) {
        throw std::invalid_argument("The rating of the review must be a number between 0 and 5 inclusive.");
    }
}

void ReviewValidator::validateComment(const std::string& comment) {
    if (comment.length() > 1000) {
        throw std::invalid_argument("The comment cannot exceed 1000 characters.");
    }
}