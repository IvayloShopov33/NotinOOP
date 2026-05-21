#include "User.h"
#include "UserCredentialsValidator.h"
#include "UserVisitor.h"

int User::nextId = 0;

User::User(const std::string& username, const std::string& password) {
    UserCredentialsValidator::validateUsername(username);
    UserCredentialsValidator::validatePassword(password);

    this->id = ++nextId;
    this->username = username;
    this->password = password;
}

// Implementation of the constructor when reading from a file
User::User(int existingId, const std::string& username, const std::string& password) {
    UserCredentialsValidator::validateUsername(username);
    UserCredentialsValidator::validatePassword(password);

    this->id = existingId;
    this->username = username;
    this->password = password;

    if (existingId >= nextId) {
        nextId = existingId + 1;
    }
}

int User::getId() const {
    return id;
}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password;
}