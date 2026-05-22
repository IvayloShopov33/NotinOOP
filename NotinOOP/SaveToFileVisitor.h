#pragma once
#include "UserVisitor.h"
#include <fstream>

class Buyer;
class Admin;

class SaveToFileVisitor : public UserVisitor {
private:
    std::ofstream& file;

public:
    // Constructor that requires an open file when creating the Visitor
    explicit SaveToFileVisitor(std::ofstream& outStream) : file(outStream) {}

    void visit(Buyer& buyer) override;
    void visit(Admin& admin) override;
};