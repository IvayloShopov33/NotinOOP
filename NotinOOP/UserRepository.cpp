#include <algorithm>
#include <vector>

#include "UserRepository.h"

void UserRepository::addUser(std::shared_ptr<User> user) {
    if (user) {
        users.push_back(std::move(user));
    }
}

std::shared_ptr<User> UserRepository::findById(int id) const {
    auto it = std::find_if(users.begin(), users.end(),
        [id](const std::shared_ptr<User>& user) {
            return user->getId() == id;
        });

    if (it != users.end()) {
        return *it;
    }

    return nullptr;
}

std::shared_ptr<User> UserRepository::findByUsername(const std::string& username) const {
    auto it = std::find_if(users.begin(), users.end(),
        [&username](const std::shared_ptr<User>& user) {
            return user->getUsername() == username;
        });

    if (it != users.end()) {
        return *it;
    }

    return nullptr;
}

bool UserRepository::removeUser(int id) {
    auto removedCount = std::erase_if(users, [id](const std::shared_ptr<User>& user) {
        return user->getId() == id;
        });

    return removedCount > 0;
}

const std::vector<std::shared_ptr<User>>& UserRepository::getAll() const {
    return users;
}