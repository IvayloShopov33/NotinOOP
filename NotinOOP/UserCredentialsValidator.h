#pragma once
#include <string>

class UserCredentialsValidator {
public:
    static void validateUsername(const std::string& username);
    static void validatePassword(const std::string& password);
};