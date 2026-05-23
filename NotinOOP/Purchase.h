#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "Fragrance.h"
#include "Discount.h"

enum class PurchaseStatus {
    PENDING,
    DELIVERED,
    CANCELED
};

class Purchase {
public:
    // A structure that seals the condition of the perfume at the time of purchase
    struct PurchaseItem {
        std::shared_ptr<Fragrance> fragrance = nullptr;
        double historicalPrice = 0.0;
    };

private:
    static int nextId;

    int purchaseId;
    int userId;

    std::vector<PurchaseItem> items;
    PurchaseStatus status;
    std::shared_ptr<Discount> appliedDiscount;

    void initialize(int userId, const std::vector<std::shared_ptr<Fragrance>>& inputFragrances,
        PurchaseStatus status, std::shared_ptr<Discount> discount);

public:
    Purchase(int userId, const std::vector<std::shared_ptr<Fragrance>>& fragrances,
        std::shared_ptr<Discount> discount = nullptr);
    Purchase(int existingId, int userId, const std::vector<std::shared_ptr<Fragrance>>& fragrances,
        PurchaseStatus status, std::shared_ptr<Discount> discount = nullptr);

    int getPurchaseId() const;
    int getUserId() const;
    PurchaseStatus getStatus() const;
    const std::vector<PurchaseItem>& getItems() const;
    std::shared_ptr<Discount> getAppliedDiscount() const;

    void setStatus(PurchaseStatus newStatus);

    double calculateTotalPrice() const;
    void show(std::ostream& os = std::cout) const;
};