#include "Admin.h"
#include "Buyer.h"
#include "Fragrance.h"
#include "Discount.h"
#include "SaveToFileVisitor.h"

void SaveToFileVisitor::visit(const Buyer& buyer) {
    file << "BUYER " << buyer.getId() << " "
        << buyer.getUsername() << " "
        << buyer.getPassword() << " "
        << buyer.getBalance() << " "
        << buyer.getRemovedReviewsCount() << " ";

    const auto& cart = buyer.getCart();
    file << "CART " << cart.size() << " ";
    for (const auto& weakFrag : cart) {
        auto sharedFrag = weakFrag.lock();
        if (sharedFrag) {
            file << sharedFrag->getId() << " ";
        }
        else {
            file << -1 << " "; // A marker if the perfume has been deleted from the catalog
        }
    }

    const auto& wishlist = buyer.getWishlist();
    file << "WISH " << wishlist.size() << " ";
    for (const auto& weakFrag : wishlist) {
        auto sharedFrag = weakFrag.lock();
        if (sharedFrag) {
            file << sharedFrag->getId() << " ";
        }
        else {
            file << -1 << " ";
        }
    }

	const auto& discounts = buyer.getDiscounts();
    file << " DISC " << discounts.size() << " ";
    for (const auto& disc : discounts) {
        if (disc) {
            file << disc->getDiscountId() << " ";
        }
        else {
            file << -1 << " ";
        }
    }

    file << "\n";
}

void SaveToFileVisitor::visit(const Admin& admin) {
    file << "ADMIN " << admin.getId() << " "
        << admin.getUsername() << " "
        << admin.getPassword() << "\n";
}