#include <stdexcept>

#include "Buyer.h"
#include "UserVisitor.h"

Buyer::Buyer(const std::string& username, const std::string& password, double balance)
    : User(username, password), balance(balance) {
    if (balance < 0) {
        throw std::invalid_argument("The balance cannot be negative.");
    }
}

Buyer::Buyer(int id, const std::string& username, const std::string& password, double balance)
    : User(id, username, password), balance(balance) {
    if (balance < 0) {
        throw std::invalid_argument("The balance cannot be negative.");
    }
}

void Buyer::accept(UserVisitor& visitor) {
    visitor.visit(*this);
}

double Buyer::getBalance() const {
    return balance;
}

void Buyer::addToBalance(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("The amount must be positive.");
    }

    balance += amount;
}

void Buyer::deductBalance(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("The amount must be positive.");
    }

    if (amount > balance) {
        throw std::runtime_error("Insufficient funds in the account.");
    }

    balance -= amount;
}

void Buyer::addToCart(std::weak_ptr<Fragrance> fragrance) {
    cart.push_back(fragrance);
}

void Buyer::addToWishlist(std::weak_ptr<Fragrance> fragrance) {
    wishlist.push_back(fragrance);
}

void Buyer::clearCart() {
    cart.clear();
}

const std::vector<std::weak_ptr<Fragrance>>& Buyer::getCart() const {
    return cart;
}

const std::vector<std::weak_ptr<Fragrance>>& Buyer::getWishlist() const {
    return wishlist;
}

void Buyer::addPurchase(std::shared_ptr<Purchase> purchase) {
    purchases.push_back(purchase);
}

const std::vector<std::shared_ptr<Purchase>>& Buyer::getPurchases() const {
    return purchases;
}