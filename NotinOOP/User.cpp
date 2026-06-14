#include "User.h"
#include "UserCredentialsValidator.h"
#include "UserVisitor.h"
#include "PasswordHasher.h"

int User::nextId = 0;

User::User(const std::string& username, const std::string& password) {
    UserCredentialsValidator::validateUsername(username);
    UserCredentialsValidator::validatePassword(password);

    this->id = ++nextId;
    this->username = username;
    this->password = PasswordHasher::hash(password);
}

// Implementation of the constructor when reading from a file
User::User(int existingId, const std::string& username, const std::string& passwordHash) {
    UserCredentialsValidator::validateUsername(username);

    this->id = existingId;
    this->username = username;
    this->password = passwordHash;

    if (existingId >= nextId) {
        nextId = existingId;
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

void User::applyReviewPenalty() {
    // Base users have no penalty, but this can be overridden in derived classes
}

bool User::shouldBeBlocked() const {
    // Base users are never blocked, but this can be overridden in derived classes
    return false;
}