#pragma once
#include <functional>
#include "UserModifierVisitor.h"

class BuyerActionVisitor : public UserModifierVisitor {
private:
    std::function<void(Buyer&)> action;
    bool isBuyer;

public:
    BuyerActionVisitor(std::function<void(Buyer&)> actionFunc);

    void visit(Buyer& buyer) override;
    void visit(Admin& admin) override;

    bool wasExecuted() const;
};