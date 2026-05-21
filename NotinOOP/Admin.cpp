#include "Admin.h"
#include "UserVisitor.h"

Admin::Admin(const std::string& username, const std::string& password)
    : User(username, password) {}

Admin::Admin(int id, const std::string& username, const std::string& password)
    : User(id, username, password) {}

void Admin::accept(UserVisitor& visitor) {
    visitor.visit(*this);
}