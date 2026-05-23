#pragma once
#include <string>

class Discount {
protected:
    static int nextId;

    int discountId;
    double discountPercent;

    void initialize(double discountPercent);

public:
    Discount(double discountPercent);
    Discount(int existingId, double discountPercent);

    int getDiscountId() const;
    double getDiscountPercent() const;

    virtual double apply(double originalPrice, const std::string& brand) const;

    virtual ~Discount() = default;
};