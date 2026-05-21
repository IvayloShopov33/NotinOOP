#include <stdexcept>
#include "UserCredentialsValidator.h"

void UserCredentialsValidator::validateUsername(const std::string& username) {
    if (username.length() < 3) {
        throw std::invalid_argument("Username must be at least 3 characters long.");
    }

    if (username.find(' ') != std::string::npos) {
        throw std::invalid_argument("Username cannot contain spaces.");
    }
}

void UserCredentialsValidator::validatePassword(const std::string& password) {
    if (password.length() < 8) {
        throw std::invalid_argument("The password must be at least 8 characters.");
    }

    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;

    for (char ch : password) {
        if (ch >= 'A' && ch <= 'Z') {
            hasUpper = true;
        }
        else if (ch >= 'a' && ch <= 'z') {
            hasLower = true;
        }
        else if (ch >= '0' && ch <= '9') {
            hasDigit = true;
        }
    }

    if (!hasUpper || !hasLower || !hasDigit) {
        throw std::invalid_argument("Password must contain at least 1 uppercase letter, 1 lowercase letter, and 1 number.");
    }
}