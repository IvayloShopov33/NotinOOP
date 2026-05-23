#pragma once
#include <vector>
#include <memory>

#include "Fragrance.h"

class PurchaseValidator {
public:
    static void validateUserId(int userId);
    static void validateFragrances(const std::vector<std::shared_ptr<Fragrance>>& fragrances);
};