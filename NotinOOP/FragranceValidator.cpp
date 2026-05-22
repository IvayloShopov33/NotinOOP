#include "FragranceValidator.h"
#include <stdexcept>

void FragranceValidator::validatePrice(double price) {
    if (price <= 0) {
        throw std::invalid_argument("The price must be a positive number.");
    }
}

void FragranceValidator::validateQuantity(int quantity) {
    if (quantity < 0) {
        throw std::invalid_argument("The quantity cannot be negative.");
    }
}

void FragranceValidator::validateAmount(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("The amount of change must be positive.");
    }
}

void FragranceValidator::validateSufficientQuantity(int requestedAmount, int availableQuantity) {
    if (requestedAmount > availableQuantity) {
        throw std::runtime_error("Insufficient quantity available for the requested fragrance.");
    }
}