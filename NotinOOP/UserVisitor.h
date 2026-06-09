#pragma once

// Preliminary declarations of concrete classes
class Buyer;
class Admin;

class UserVisitor {
public:
    virtual ~UserVisitor() = default;

    virtual void visit(const Buyer& buyer) = 0;
    virtual void visit(const Admin& admin) = 0;
};