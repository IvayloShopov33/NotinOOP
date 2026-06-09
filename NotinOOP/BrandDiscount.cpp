#include "BrandDiscount.h"
#include "TextValidator.h"

void BrandDiscount::initialize(const std::string& brandName) {
    TextValidator::validateName(brandName, "The target brand for the discount");
    this->brandName = brandName;
}

BrandDiscount::BrandDiscount(double discountPercent, const std::string& brandName)
    : Discount(discountPercent)
{
    initialize(brandName);
}

BrandDiscount::BrandDiscount(int existingId, double discountPercent, const std::string& brandName)
    : Discount(existingId, discountPercent)
{
    initialize(brandName);
}

const std::string& BrandDiscount::getBrandName() const {
    return brandName;
}

double BrandDiscount::apply(double originalPrice, const std::string& brand) const {
    if (brand == brandName) {
        return Discount::apply(originalPrice, brand);
    }

    return originalPrice;
}

std::string BrandDiscount::serialize() const {
    return "BRAND " + std::to_string(discountId) + " " +
        std::to_string(discountPercent) + " " + brandName;
}