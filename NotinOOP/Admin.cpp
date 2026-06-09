#include "Admin.h"
#include "UserVisitor.h"

Admin::Admin(const std::string& username, const std::string& password)
    : User(username, password) {}

Admin::Admin(int id, const std::string& username, const std::string& password)
    : User(id, username, password) {}

bool Admin::isAdmin() const { return true; }

void Admin::accept(UserVisitor& visitor) const {
    visitor.visit(*this);
}