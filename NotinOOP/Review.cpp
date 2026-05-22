#include "Review.h"
#include "ReviewValidator.h"
#include "TextValidator.h"

int Review::nextId = 0;

void Review::initialize(const std::string& fragranceName, int userId, const std::string& comment, int rating) {
    TextValidator::validateName(fragranceName, "Fragrance name in the review");

    ReviewValidator::validateComment(comment);
    ReviewValidator::validateRating(rating);

    this->fragranceName = fragranceName;
    this->userId = userId;
    this->comment = comment;
    this->rating = rating;
}

Review::Review(const std::string& fragranceName, int userId, const std::string& comment, int rating) {
	initialize(fragranceName, userId, comment, rating);

    this->id = ++nextId;
}

Review::Review(int existingId, const std::string& fragranceName, int userId, const std::string& comment, int rating) {
	initialize(fragranceName, userId, comment, rating);

    this->id = existingId;
    if (existingId >= nextId) {
        nextId = existingId + 1;
    }
}

int Review::getId() const {
    return id;
}

const std::string& Review::getFragranceName() const {
    return fragranceName;
}

int Review::getUserId() const {
    return userId;
}

const std::string& Review::getComment() const {
    return comment;
}

int Review::getRating() const {
    return rating;
}