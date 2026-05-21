#pragma once

// Preliminary declarations of concrete classes
class Buyer;
class Admin;

class UserVisitor {
public:
    virtual ~UserVisitor() = default;

    virtual void visit(Buyer& buyer) = 0;
    virtual void visit(Admin& admin) = 0;
};