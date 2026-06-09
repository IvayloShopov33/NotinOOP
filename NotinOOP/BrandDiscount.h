#pragma once
#include "Discount.h"
#include <string>

class BrandDiscount : public Discount {
private:
    std::string brandName;

    void initialize(const std::string& brandName);

public:
    BrandDiscount(double discountPercent, const std::string& brandName);
    BrandDiscount(int existingId, double discountPercent, const std::string& brandName);

    const std::string& getBrandName() const;

    double apply(double originalPrice, const std::string& brand) const override;
    std::string serialize() const override;
};