#include "HelpVisitor.h"
#include <iostream>

void HelpVisitor::visit(const Buyer& buyer) {
    std::cout << "[Role: BUYER]\n";
    std::cout << "add-to-balance <amount>                           - Top up your balance\n";
    std::cout << "add-to-cart / remove-from-cart <frag-name>        - Manage your cart\n";
    std::cout << "add-to-wishlist / remove-from-wishlist <frag>     - Manage your wishlist\n";
    std::cout << "view-cart / view-bought / view-purchases          - View shop sections\n";
    std::cout << "recommend                                         - Get 3 perfume recommendations\n";
    std::cout << "checkout                                          - Complete order with best discount\n";
    std::cout << "cancel <purchase-id>                              - Cancel a PENDING order\n";
    std::cout << "make-review <frag-name> <rating> <comment>        - Write a perfume review\n";
}

void HelpVisitor::visit(const Admin& admin) {
    std::cout << "[Role: ADMIN]\n";
    std::cout << "block-user <username>                             - Block user and delete account\n";
    std::cout << "create-fragrance <name> <brand> <price> <family>  - Add new perfume\n";
    std::cout << "add-quantity <fragrance-name> <quantity>          - Restock perfume\n";
    std::cout << "deliver <purchase-id>                             - Simulate successful delivery\n";
    std::cout << "remove-review <fragrance-id> <review-id>          - Delete a specific review\n";
}