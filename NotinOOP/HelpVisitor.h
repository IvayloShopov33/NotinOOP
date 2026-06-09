#pragma once
#include "UserVisitor.h"

class HelpVisitor : public UserVisitor {
public:
    void visit(const Buyer& buyer) override;
    void visit(const Admin& admin) override;
};