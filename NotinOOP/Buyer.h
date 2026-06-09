#pragma once
#include "User.h"
#include <vector>
#include <memory>

// Pre-declarations - tell the compiler that these classes exist
class Fragrance;
class Purchase;

class Buyer : public User {
private:
    double balance = 0.0;
    int removedReviewsCount = 0;
    std::vector<std::weak_ptr<Fragrance>> cart;
    std::vector<std::weak_ptr<Fragrance>> wishlist;
    std::vector<std::shared_ptr<Purchase>> purchases;

public:
    Buyer(const std::string& username, const std::string& password, double balance = 0.0);

    // Constructor for loading an existing buyer from a file
    Buyer(int id, const std::string& username, const std::string& password, double balance);

	virtual bool isAdmin() const override;

    // Double Dispatch implementation for the Visitor pattern
    void accept(UserVisitor& visitor) const override;
    void acceptModifier(UserModifierVisitor& visitor) override;

    double getBalance() const;
    void addToBalance(double amount);
    void deductBalance(double amount);

    void addToCart(std::weak_ptr<Fragrance> fragrance);
    bool removeFromCart(int fragranceId);
    void clearCart();

    void addToWishlist(std::weak_ptr<Fragrance> fragrance);
    bool removeFromWishlist(int fragranceId);

    int getRemovedReviewsCount() const;
    void incrementRemovedReviews();
    void setRemovedReviewsCount(int count);

    const std::vector<std::weak_ptr<Fragrance>>& getCart() const;
    const std::vector<std::weak_ptr<Fragrance>>& getWishlist() const;

    void addPurchase(std::shared_ptr<Purchase> purchase);
    const std::vector<std::shared_ptr<Purchase>>& getPurchases() const;

    void applyReviewPenalty() override;
    bool shouldBeBlocked() const override;
};