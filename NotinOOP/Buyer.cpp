#include <stdexcept>

#include "Buyer.h"
#include "Fragrance.h"
#include "Discount.h"

#include "UserVisitor.h"
#include "UserModifierVisitor.h"

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

bool Buyer::isAdmin() const { return false; }

void Buyer::accept(UserVisitor& visitor) const {
    visitor.visit(*this);
}

void Buyer::acceptModifier(UserModifierVisitor& visitor) {
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

bool Buyer::removeFromCart(int fragranceId) {
    for (auto it = cart.begin(); it != cart.end(); it++) {
        if (auto fragPtr = it->lock()) {
            if (fragPtr->getId() == fragranceId) {
                cart.erase(it);

                return true;
            }
        }
    }

    return false;
}

void Buyer::clearCart() {
    cart.clear();
}

void Buyer::addToWishlist(std::weak_ptr<Fragrance> fragrance) {
    wishlist.push_back(fragrance);
}

bool Buyer::removeFromWishlist(int fragranceId) {
    for (auto it = wishlist.begin(); it != wishlist.end(); it++) {
        if (auto fragPtr = it->lock()) {
            if (fragPtr->getId() == fragranceId) {
                wishlist.erase(it);

                return true;
            }
        }
    }

    return false;
}

int Buyer::getRemovedReviewsCount() const {
    return removedReviewsCount;
}

void Buyer::incrementRemovedReviews() {
    removedReviewsCount++;
}

void Buyer::setRemovedReviewsCount(int count) {
    if (count < 0) {
        throw std::invalid_argument("The count of removed reviews cannot be negative.");
    }

    removedReviewsCount = count;
}

void Buyer::addDiscount(std::shared_ptr<Discount> discount) {
    if (discount) {
        discounts.push_back(discount);
    }
}

void Buyer::removeDiscount(int discountId) {
    for (auto it = discounts.begin(); it != discounts.end(); it++) {
        if ((*it)->getDiscountId() == discountId) {
            discounts.erase(it);

            break;
        }
    }
}

const std::vector<std::shared_ptr<Discount>>& Buyer::getDiscounts() const {
    return discounts;
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

void Buyer::applyReviewPenalty() { removedReviewsCount++; }

bool Buyer::shouldBeBlocked() const { return removedReviewsCount >= 7; }