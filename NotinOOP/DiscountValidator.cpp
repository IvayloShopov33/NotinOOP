#include "DiscountValidator.h"
#include <stdexcept>

void DiscountValidator::validatePercentage(double percentage) {
    if (percentage < 0.0 || percentage > 100.0) {
        throw std::invalid_argument("The discount percentage must be between 0 and 100.");
    }
}

void DiscountValidator::validateFixedAmount(double amount) {
    if (amount < 0.0) {
        throw std::invalid_argument("The fixed discount cannot be a negative amount.");
    }
}