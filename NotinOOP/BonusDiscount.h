#pragma once
#include "Discount.h"

class BonusDiscount : public Discount {
private:
    double bonus;

    void initialize(double bonusAmount);

public:
    BonusDiscount(double discountPercent, double bonusAmount);
    BonusDiscount(int existingId, double discountPercent, double bonusAmount);

    double getBonus() const;

    double apply(double originalPrice, const std::string& brand) const override;
    std::string serialize() const override;
};