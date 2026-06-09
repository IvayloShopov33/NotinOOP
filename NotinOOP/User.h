#pragma once
#include <string>

// Visitor's preliminary declaration
class UserVisitor;
class UserModifierVisitor;

class User {
protected:
    static int nextId;

    int id;
    std::string username;
    std::string password;

public:
    User(const std::string& username, const std::string& password);

    User(int existingId, const std::string& username, const std::string& password);

    virtual bool isAdmin() const = 0;

	// Entry point for the Visitor pattern
    virtual void accept(UserVisitor& visitor) const = 0;
    virtual void acceptModifier(UserModifierVisitor& visitor) = 0;

    int getId() const;
    const std::string& getUsername() const;
    const std::string& getPassword() const;

    virtual void applyReviewPenalty();
    virtual bool shouldBeBlocked() const;

    virtual ~User() = default;
};