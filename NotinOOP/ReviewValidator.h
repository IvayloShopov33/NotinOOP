#pragma once
#include <string>

class ReviewValidator {
public:
    static void validateRating(int rating);
    static void validateComment(const std::string& comment);
};