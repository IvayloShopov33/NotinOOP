#include "SaveToFileVisitor.h"
#include "Buyer.h"
#include "Admin.h"

void SaveToFileVisitor::visit(Buyer& buyer) {
    file << "BUYER " << buyer.getId() << " "
        << buyer.getUsername() << " "
        << buyer.getPassword() << " "
        << buyer.getBalance() << "\n";
}

void SaveToFileVisitor::visit(Admin& admin) {
    file << "ADMIN " << admin.getId() << " "
        << admin.getUsername() << " "
        << admin.getPassword() << "\n";
}