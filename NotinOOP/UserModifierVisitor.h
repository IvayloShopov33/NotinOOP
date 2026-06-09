#pragma once

class Buyer;
class Admin;

class UserModifierVisitor {
public:
    virtual void visit(Buyer& buyer) = 0;
    virtual void visit(Admin& admin) = 0;

    virtual ~UserModifierVisitor() = default;
};