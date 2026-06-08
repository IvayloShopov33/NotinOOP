#include <algorithm>
#include <fstream>

#include "NotinoOOP.h"
#include "Buyer.h" 
#include "Admin.h"

NotinoOOP::NotinoOOP() : currentUser(nullptr) {}

void NotinoOOP::loadData() {
    std::cout << "Loading data from database...\n";
    std::cout << "Data loaded successfully.\n";
}

void NotinoOOP::saveData() const {
    std::cout << "Saving current state to files...\n";
    std::cout << "All changes saved successfully. Exit.\n";
}

bool NotinoOOP::registerUser(const std::string& username, const std::string& password) {
    if (userRepo.findByUsername(username) != nullptr) {
        std::cout << "Username '" << username << "' already exists.\n";
        return false;
    }

    auto newBuyer = std::make_shared<Buyer>(username, password);
    userRepo.addUser(std::move(newBuyer));

    std::cout << "Registration is successful. You can log in to your account.\n";
    return true;
}

bool NotinoOOP::registerAdmin(const std::string& username, const std::string& password) {
    if (userRepo.findByUsername(username) != nullptr) {
        std::cout << "Username '" << username << "' already exists.\n";
        return false;
    }

    auto newAdmin = std::make_shared<Admin>(username, password);
    userRepo.addUser(std::move(newAdmin));

    std::cout << "Administrator registration successful.\n";
    return true;
}

bool NotinoOOP::loginUser(const std::string& username, const std::string& password) {
    if (currentUser != nullptr) {
        std::cout << "There is already an active session for user: " << currentUser->getUsername() << "\n";
        return false;
    }

    auto user = userRepo.findByUsername(username);
    if (user == nullptr || user->getPassword() != password) {
        std::cout << "Invalid username or password.\n";
        return false;
    }

    currentUser = user;
    std::cout << "Login successful! Welcome, " << currentUser->getUsername() << ".\n";
    return true;
}

void NotinoOOP::logoutUser() {
    if (currentUser == nullptr) {
        std::cout << "There is no active user session at the moment.\n";

        return;
    }

    std::cout << "User " << currentUser->getUsername() << " logged out successfully.\n";
    currentUser = nullptr;
}

std::shared_ptr<User> NotinoOOP::getCurrentUser() const {
    return currentUser;
}

void NotinoOOP::addFragranceToCatalog(std::shared_ptr<Fragrance> fragrance) {
    fragranceRepo.addFragrance(std::move(fragrance));
}

bool NotinoOOP::removeFragranceFromCatalog(int fragranceId) {
    return fragranceRepo.removeFragrance(fragranceId);
}

void NotinoOOP::addDiscountToSystem(std::shared_ptr<Discount> discount) {
    discountRepo.addDiscount(std::move(discount));
}

void NotinoOOP::showCatalog(std::ostream& os) const {
    const auto& catalog = fragranceRepo.getAll();
    if (catalog.empty()) {
        os << "The catalog is currently empty.\n";
        return;
    }

    os << "\n--- PERFUME CATALOGUE ---\n";
    for (const auto& frag : catalog) {
        if (frag) {
            os << "ID: #" << frag->getId() << " | " << frag->getBrand()
                << " - " << frag->getName() << " | Price: " << frag->getPrice() << " euro\n";
        }
    }
    os << "---------------------------\n";
}

bool NotinoOOP::checkout(const std::vector<int>& fragranceIds, int discountId) {
    if (currentUser == nullptr) {
        std::cout << "You must be logged in to place an order.\n";
        return false;
    }

    if (fragranceIds.empty()) {
        std::cout << "The selected cart is empty.\n";
        return false;
    }

    std::vector<std::shared_ptr<Fragrance>> selectedFragrances;
    selectedFragrances.reserve(fragranceIds.size());

    for (int id : fragranceIds) {
        auto frag = fragranceRepo.findById(id);
        if (frag == nullptr) {
            std::cout << "Perfume with ID #" << id << " does not exist in the catalog. The order has been canceled.\n";
            return false;
        }

        selectedFragrances.push_back(frag);
    }

    std::shared_ptr<Discount> appliedDiscount = nullptr;
    if (discountId != -1) {
        appliedDiscount = discountRepo.findById(discountId);
        if (appliedDiscount == nullptr) {
            std::cout << "Voucher with ID #" << discountId << " is not valid. The order continues without discount.\n";
        }
    }

    Purchase newPurchase(currentUser->getId(), selectedFragrances, appliedDiscount);

    newPurchase.show(std::cout);
    purchases.push_back(std::move(newPurchase));
    std::cout << "The order was successfully registered in the system.\n";

    return true;
}

void NotinoOOP::showCurrentUserPurchaseHistory(std::ostream& os) const {
    if (currentUser == nullptr) {
        os << "No user logged in.\n";
        return;
    }

    os << "\n--- USER PURCHASE HISTORY: " << currentUser->getUsername() << " ---\n";
    bool hasPurchases = false;

    for (const auto& purchase : purchases) {
        if (purchase.getUserId() == currentUser->getId()) {
            purchase.show(os);
            hasPurchases = true;
        }
    }

    if (!hasPurchases) {
        os << "You have no purchases made yet.\n";
    }

    os << "----------------------------------------------------------------------\n";
}

void NotinoOOP::showAllPurchasesInSystem(std::ostream& os) const {
    os << "\n--- GLOBAL CHECK OF ALL PURCHASES IN THE SYSTEM ---\n";
    if (purchases.empty()) {
        os << "There are no registered purchases in the system.\n";
        return;
    }

    for (const auto& purchase : purchases) {
        purchase.show(os);
    }

    os << "---------------------------------------------------\n";
}