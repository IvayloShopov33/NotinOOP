#pragma once
#include <vector>
#include <memory>
#include <string>

#include "User.h"

class UserRepository {
private:
    std::vector<std::shared_ptr<User>> users;

public:
    void addUser(std::shared_ptr<User> user);

    std::shared_ptr<User> findById(int id) const;

    std::shared_ptr<User> findByUsername(const std::string& username) const;

    bool removeUser(int id);

    const std::vector<std::shared_ptr<User>>& getAll() const;
};