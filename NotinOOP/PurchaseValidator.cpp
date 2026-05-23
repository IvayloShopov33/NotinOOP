#include <stdexcept>

#include "PurchaseValidator.h"

void PurchaseValidator::validateUserId(int userId) {
    if (userId <= 0) {
        throw std::invalid_argument("The user ID must be positive.");
    }
}

void PurchaseValidator::validateFragrances(const std::vector<std::shared_ptr<Fragrance>>& fragrances) {
    if (fragrances.empty()) {
        throw std::invalid_argument("The purchase must contain at least one perfume.");
    }
}