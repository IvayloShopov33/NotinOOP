#include <algorithm>

#include "BonusDiscount.h"
#include "DiscountValidator.h"

void BonusDiscount::initialize(double bonusAmount) {
    DiscountValidator::validateFixedAmount(bonusAmount);
    this->bonus = bonusAmount;
}

BonusDiscount::BonusDiscount(double discountPercent, double bonusAmount)
    : Discount(discountPercent)
{
    initialize(bonusAmount);
}

BonusDiscount::BonusDiscount(int existingId, double discountPercent, double bonusAmount)
    : Discount(existingId, discountPercent)
{
    initialize(bonusAmount);
}

double BonusDiscount::getBonus() const {
    return bonus;
}

double BonusDiscount::apply(double originalPrice, const std::string& brand) const {
    double priceAfterPercentage = Discount::apply(originalPrice, brand);

    return std::max(0.0, priceAfterPercentage - bonus);
}

std::string BonusDiscount::serialize() const {
    return "BONUS " + std::to_string(discountId) + " " +
        std::to_string(discountPercent) + " " + std::to_string(bonus);
}