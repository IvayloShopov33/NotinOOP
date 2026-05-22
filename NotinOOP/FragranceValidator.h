#pragma once

class FragranceValidator {
public:
    static void validatePrice(double price);
    static void validateQuantity(int quantity);
    static void validateAmount(int amount);
	static void validateSufficientQuantity(int requestedAmount, int availableQuantity);
};