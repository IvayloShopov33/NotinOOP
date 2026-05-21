#pragma once
#include "User.h"

class Admin : public User {
public:
    Admin(const std::string& username, const std::string& password);

    Admin(int id, const std::string& username, const std::string& password);

    // Double Dispatch implementation for the Visitor pattern
    void accept(UserVisitor& visitor) override;
};