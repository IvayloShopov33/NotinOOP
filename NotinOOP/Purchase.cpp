#include <iostream>
#include <iomanip>

#include "Purchase.h"
#include "PurchaseValidator.h"

int Purchase::nextId = 0;

static std::string statusToString(PurchaseStatus status) {
    switch (status) {
    case PurchaseStatus::PENDING:
        return "PENDING";
    case PurchaseStatus::DELIVERED:
        return "DELIVERED";
    case PurchaseStatus::CANCELED:
        return "CANCELED";
    default:
        return "UNKNOWN";
    }
}

void Purchase::initialize(int userId, const std::vector<std::shared_ptr<Fragrance>>& inputFragrances,
    PurchaseStatus status, std::shared_ptr<Discount> discount) {

    PurchaseValidator::validateUserId(userId);
    PurchaseValidator::validateFragrances(inputFragrances);

    this->userId = userId;
    this->status = status;
    this->appliedDiscount = discount;

    this->items.reserve(inputFragrances.size());
    for (const auto& frag : inputFragrances) {
        if (frag) {
            PurchaseItem item;
            item.fragrance = frag;
            item.historicalPrice = frag->getPrice();
            this->items.push_back(std::move(item));
        }
    }
}

Purchase::Purchase(int userId, const std::vector<std::shared_ptr<Fragrance>>& fragrances,
    std::shared_ptr<Discount> discount) {
    initialize(userId, fragrances, PurchaseStatus::PENDING, discount);

    this->purchaseId = ++nextId;
}

Purchase::Purchase(int existingId, int userId, const std::vector<std::shared_ptr<Fragrance>>& fragrances,
    PurchaseStatus status, std::shared_ptr<Discount> discount) {
    initialize(userId, fragrances, status, discount);

    this->purchaseId = existingId;
    if (existingId >= nextId) {
        nextId = existingId + 1;
    }
}

int Purchase::getPurchaseId() const { return purchaseId; }
int Purchase::getUserId() const { return userId; }
PurchaseStatus Purchase::getStatus() const { return status; }

const std::vector<Purchase::PurchaseItem>& Purchase::getItems() const { return items; }
std::shared_ptr<Discount> Purchase::getAppliedDiscount() const { return appliedDiscount; }

void Purchase::setStatus(PurchaseStatus newStatus) {
    this->status = newStatus;
}

double Purchase::calculateTotalPrice() const {
    double total = 0.0;

    for (const auto& item : items) {
        if (appliedDiscount) {
            total += appliedDiscount->apply(item.historicalPrice, item.fragrance->getBrand());
        }
        else {
            total += item.historicalPrice;
        }
    }

    return total;
}

void Purchase::show(std::ostream& os) const {
    os << "==================================================\n";
    os << "ORDER ID: #" << purchaseId << "\n";
    os << "--------------------------------------------------\n";
    os << "Buyer (User ID): " << userId << "\n";
    os << "Order status: " << statusToString(status) << "\n";
    os << "List of items:\n";

    for (const auto& item : items) {
        os << "  * " << item.fragrance->getBrand() << " - " << item.fragrance->getName()
            << " [" << std::fixed << std::setprecision(2) << item.historicalPrice << " euro]\n";
    }

    if (appliedDiscount) {
        os << "Discount voucher ID attached: #" << appliedDiscount->getDiscountId() << "\n";
    }

    os << "--------------------------------------------------\n";
    os << "TOTAL ORDER AMOUNT: " << std::fixed << std::setprecision(2)
        << calculateTotalPrice() << " euro\n";
    os << "==================================================\n";
}