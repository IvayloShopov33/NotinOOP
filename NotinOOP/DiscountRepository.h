#pragma once
#include <vector>
#include <memory>

#include "Discount.h"

class DiscountRepository {
private:
    std::vector<std::shared_ptr<Discount>> discounts;

public:
    void addDiscount(std::shared_ptr<Discount> discount);

    std::shared_ptr<Discount> findById(int id) const;

    const std::vector<std::shared_ptr<Discount>>& getAll() const;
};