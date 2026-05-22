#include "TextValidator.h"
#include <stdexcept>

void TextValidator::validateName(const std::string& name, const std::string& fieldName) {
    if (name.empty()) {
        throw std::invalid_argument(fieldName + " cannot be empty.");
    }
    if (name.length() < 2) {
        throw std::invalid_argument(fieldName + " must contain at least 2 symbols.");
    }
    if (name.length() > 100) {
        throw std::invalid_argument(fieldName + " is too long (maximum is 100 symbols).");
    }
}