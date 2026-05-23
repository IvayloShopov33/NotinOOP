#include <algorithm>

#include "DiscountRepository.h"

void DiscountRepository::addDiscount(std::shared_ptr<Discount> discount) {
    if (discount) {
        discounts.push_back(std::move(discount));
    }
}

std::shared_ptr<Discount> DiscountRepository::findById(int id) const {
    auto it = std::find_if(discounts.begin(), discounts.end(),
        [id](const std::shared_ptr<Discount>& discount) {
            return discount->getDiscountId() == id;
        });

    if (it != discounts.end()) {
        return *it;
    }

    return nullptr;
}

const std::vector<std::shared_ptr<Discount>>& DiscountRepository::getAll() const {
    return discounts;
}