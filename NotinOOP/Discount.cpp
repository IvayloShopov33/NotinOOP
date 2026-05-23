#include "Discount.h"
#include "DiscountValidator.h"

int Discount::nextId = 0;

void Discount::initialize(double discountPercent) {
    DiscountValidator::validatePercentage(discountPercent);
    this->discountPercent = discountPercent;
}

Discount::Discount(double discountPercent) {
    initialize(discountPercent);

    this->discountId = ++nextId;
}

Discount::Discount(int existingId, double discountPercent) {
    initialize(discountPercent);

    this->discountId = existingId;
    if (existingId >= nextId) {
        nextId = existingId + 1;
    }
}

int Discount::getDiscountId() const {
    return discountId;
}

double Discount::getDiscountPercent() const {
    return discountPercent;
}

double Discount::apply(double originalPrice, const std::string& brand) const {
    return originalPrice * (1.0 - (discountPercent / 100.0));
}