#include <algorithm>
#include <fstream>
#include <string>

#include "NotinoOOP.h"
#include "Buyer.h" 
#include "Admin.h"
#include "Review.h"

#include "SaveToFileVisitor.h"
#include "BuyerActionVisitor.h"

#include "Discount.h"
#include "BrandDiscount.h"
#include "BonusDiscount.h"

NotinoOOP::NotinoOOP() : currentUser(nullptr) {}


void NotinoOOP::loadData() {
    std::cout << "Loading data from database...\n";

    std::ifstream inFile("system_data.txt");
    if (!inFile.is_open()) {
        std::cout << "No existing database found. Starting fresh.\n";
        return;
    }

    std::string currentSection = "";
    std::string token;

    while (inFile >> token) {
        // Check if the word is a section title (starts with '[' and ends with ']')
        if (token.front() == '[' && token.back() == ']') {
            currentSection = token;
            continue;
        }

        if (currentSection == "[FRAGRANCES]") {
            int id = std::stoi(token);
            std::string brand, name;
            double price;
            int quantity;
            size_t familySize;

            inFile >> brand >> name >> price >> quantity >> familySize;

            if (!inFile.fail()) {
                std::vector<std::string> families;

                for (size_t i = 0; i < familySize; i++) {
                    std::string note;
                    inFile >> note;
                    families.push_back(note);
                }

                auto newFrag = std::make_shared<Fragrance>(id, name, brand, price, families, quantity);
                fragranceRepo.addFragrance(std::move(newFrag));
            }
        }
        else if (currentSection == "[DISCOUNTS]") {
            std::string discountType = token;
            int id;
            double percent;

            inFile >> id;
            inFile >> percent;

            if (discountType == "BONUS") {
                double bonusAmount;
                inFile >> bonusAmount;

                if (!inFile.fail()) {
                    discountRepo.addDiscount(std::make_shared<BonusDiscount>(id, percent, bonusAmount));
                }
            }
            else if (discountType == "BRAND") {
                std::string brandName;
                inFile >> brandName;

                if (!inFile.fail()) {
                    discountRepo.addDiscount(std::make_shared<BrandDiscount>(id, percent, brandName));
                }
            }
        }
        else if (currentSection == "[USERS]") {
            std::string role = token;

            if (role == "ADMIN") {
                int id;
                std::string username, password;

                inFile >> id;
                inFile >> username;
                inFile >> password;

                if (!inFile.fail()) {
                    userRepo.addUser(std::make_shared<Admin>(id, username, password));
                }
            }
            else if (role == "BUYER") {
                int id;
                std::string username, password;
                double balance;
				int removedReviews;

                inFile >> id;
                inFile >> username;
                inFile >> password;
                inFile >> balance;
				inFile >> removedReviews;

                if (!inFile.fail()) {
                    auto buyer = std::make_shared<Buyer>(id, username, password, balance);
					buyer->setRemovedReviewsCount(removedReviews);

                    std::string marker;

                    // Cart recovery
                    inFile >> marker; // Reading the word "CART"
                    size_t cartSize;
                    inFile >> cartSize;
                    if (!inFile.fail() && marker == "CART") {
                        for (size_t i = 0; i < cartSize; i++) {
                            int fragId;
                            inFile >> fragId;

                            if (fragId != -1) {
                                auto frag = fragranceRepo.findById(fragId);
                                if (frag) {
                                    buyer->addToCart(frag);
                                }
                            }
                        }
                    }

					// Wishlist recovery
                    inFile >> marker; // Reading the word "WISH"
					size_t wishlistSize;
                    inFile >> wishlistSize;
                    if (!inFile.fail() && marker == "WISH") {
                        for (size_t i = 0; i < wishlistSize; i++) {
                            int fragId;
                            inFile >> fragId;

                            if (fragId != -1) {
                                auto frag = fragranceRepo.findById(fragId);
                                if (frag) {
                                    buyer->addToWishlist(frag);
                                }
                            }
                        }
                    }

                    userRepo.addUser(std::move(buyer));
                }
            }
        }
        else if (currentSection == "[PURCHASES]") {
            int purchaseId = std::stoi(token);
            int userId, statusInt, discountId;
            size_t itemCount;

            inFile >> userId;
            inFile >> statusInt;
            inFile >> discountId;
            inFile >> itemCount;

            if (!inFile.fail()) {
                std::vector<std::shared_ptr<Fragrance>> purchaseFrags;
                for (size_t i = 0; i < itemCount; i++) {
                    int fragId;
                    inFile >> fragId;

                    auto frag = fragranceRepo.findById(fragId);
                    if (frag) {
                        purchaseFrags.push_back(frag);
                    }
                }

                auto appliedDiscount = (discountId != -1) ? discountRepo.findById(discountId) : nullptr;
                Purchase loadedPurchase(purchaseId, userId, purchaseFrags, static_cast<PurchaseStatus>(statusInt), appliedDiscount);
                purchases.push_back(std::move(loadedPurchase));
            }
        }
        else if (currentSection == "[REVIEWS]") {
            int id = std::stoi(token);
            int userId, rating;
            std::string fragName, comment;

            inFile >> userId;
            inFile >> rating;
            inFile >> fragName;

            if (!inFile.fail()) {
                // Using getline here only for the comment because it contains spaces in the sentence
                std::getline(inFile, comment);

                // Removing the first blank space that remains before the beginning of the sentence
                if (!comment.empty() && comment[0] == ' ') {
                    comment.erase(0, 1);
                }

                reviews.push_back(Review(id, fragName, userId, comment, rating));
            }
        }
    }

    inFile.close();
    std::cout << "Data loaded successfully.\n";
}

void NotinoOOP::saveData() const {
    std::cout << "Saving current state to files...\n";
    std::ofstream outFile("system_data.txt");
    if (!outFile.is_open()) {
        std::cout << "The file cannot be opened for writing!\n";
        return;
    }

    outFile << "[FRAGRANCES]\n";
    for (const auto& frag : fragranceRepo.getAll()) {
        if (frag) {
            outFile << frag->getId() << " " << frag->getBrand() << " "
                << frag->getName() << " " << frag->getPrice() << " "
                << frag->getQuantity() << " ";

            const auto& families = frag->getfragranceFamily();
            outFile << families.size() << " ";
            for (const auto& note : families) {
                outFile << note << " ";
            }

            outFile << "\n";
        }
    }

    outFile << "[DISCOUNTS]\n";
    for (const auto& disc : discountRepo.getAll()) {
        if (disc) {
            outFile << disc->serialize() << "\n";
        }
    }

    outFile << "[USERS]\n";
    SaveToFileVisitor visitor(outFile);

    for (const auto& user : userRepo.getAll()) {
        if (user) user->accept(visitor);
    }

    outFile << "[PURCHASES]\n";
    for (const auto& purchase : purchases) {
        outFile << purchase.getPurchaseId() << " "
            << purchase.getUserId() << " "
            << static_cast<int>(purchase.getStatus()) << " ";

        if (purchase.getAppliedDiscount()) {
            outFile << purchase.getAppliedDiscount()->getDiscountId() << " ";
        }
        else {
            outFile << "-1 ";
        }

        const auto& items = purchase.getItems();
        outFile << items.size() << " ";

        for (const auto& item : items) {
            if (item.fragrance) outFile << item.fragrance->getId() << " ";
        }

        outFile << "\n";
    }

    outFile << "[REVIEWS]\n";
    for (const auto& review : reviews) {
        outFile << review.getId() << " "
            << review.getUserId() << " "
            << review.getRating() << " "
            << review.getFragranceName() << " "
            << review.getComment() << "\n";
    }

    outFile.close();
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

std::shared_ptr<Fragrance> NotinoOOP::findFragranceByName(const std::string& name) const {
    for (const auto& frag : fragranceRepo.getAll()) {
        if (frag && frag->getName() == name) {
            return frag;
        }
    }

    return nullptr;
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

bool NotinoOOP::checkout() {
    if (!currentUser) {
        std::cout << "Error! You must be logged in to complete an order.\n";

        return false;
    }

    bool isSuccessful = false;

    BuyerActionVisitor visitor([this, &isSuccessful](Buyer& buyer) {
        const auto& cart = buyer.getCart();
        if (cart.empty()) {
            std::cout << "Error! Your cart is empty.\n";

            return;
        }

        double originalTotal = 0.0;
        std::vector<std::shared_ptr<Fragrance>> validFragrances;

        for (const auto& weakFrag : cart) {
            if (auto frag = weakFrag.lock()) {
                originalTotal += frag->getPrice();
                validFragrances.push_back(std::move(frag));
            }
        }

        if (validFragrances.empty()) {
            std::cout << "Error! The selected products are no longer available.\n";
            buyer.clearCart();

            return;
        }

        double finalPrice = originalTotal;
        std::shared_ptr<Discount> bestDiscount = nullptr;

        for (const auto& discount : discountRepo.getAll()) {
            if (discount) {
                double currentDiscountTotal = 0.0;

                for (const auto& frag : validFragrances) {
                    currentDiscountTotal += discount->apply(frag->getPrice(), frag->getBrand());
                }

                if (currentDiscountTotal < finalPrice) {
                    finalPrice = currentDiscountTotal;
                    bestDiscount = discount;
                }
            }
        }

        if (buyer.getBalance() < finalPrice) {
            std::cout << "Error! Insufficient stock. Needed " << finalPrice
                << " euro, and you have " << buyer.getBalance() << " euro.\n";

            return;
        }

        buyer.deductBalance(finalPrice);

        Purchase newPurchase(buyer.getId(), validFragrances, bestDiscount);
        purchases.push_back(std::move(newPurchase));

        buyer.clearCart();
        std::cout << "Successful order! ";

        if (bestDiscount) {
            std::cout << "A voucher is attached. ";
        }

        std::cout << "Withheld " << finalPrice << " euro.\n";
        isSuccessful = true;
        });

    currentUser->acceptModifier(visitor);
    if (!visitor.wasExecuted()) {
        std::cout << "Error! Only buyers can place orders.\n";
    }

    return isSuccessful;
}

void NotinoOOP::showPurchasesFiltered(std::function<bool(const Purchase&)> filter, std::ostream& os) const {
    if (currentUser == nullptr) {
        os << "No user logged in.\n";

        return;
    }

    int currentUserId = currentUser->getId();
    bool foundAny = false;

    for (const auto& purchase : purchases) {
        // Checking if the order belongs to the current user AND if it matches the filter
        if (purchase.getUserId() == currentUserId && filter(purchase)) {
            purchase.show(os);
            foundAny = true;
        }
    }

    if (!foundAny) {
        os << "No orders found matching the criteria.\n";
    }

    os << "----------------------------------------------------------------------\n";
}

void NotinoOOP::showCurrentUserPurchaseHistory(std::ostream& os) const {
    os << "\n--- USER ALL PURCHASES HISTORY: " << currentUser->getUsername() << " ---\n";

    showPurchasesFiltered([](const Purchase& p) {
        return true;
        }, std::cout);
}

void NotinoOOP::showCurrentUserDeliveredPurchases(std::ostream& os) const {
    os << "\n--- USER ALL SUCCESSFUL PURCHASES (DELIVERED) HISTORY: " << currentUser->getUsername() << " --- \n";

    showPurchasesFiltered([](const Purchase& p) {
        return p.getStatus() == PurchaseStatus::DELIVERED;
        }, std::cout);
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

bool NotinoOOP::blockUser(const std::string& username) {
    auto user = userRepo.findByUsername(username);
    if (!user) {
        return false;
    }

    return userRepo.removeUser(user->getId());
}

// DELIVERY SIMULATION
void NotinoOOP::addQuantityToFragrance(const std::string& fragranceName, int quantity) {
    bool found = false;

    for (const auto& frag : fragranceRepo.getAll()) {
        if (frag && frag->getName() == fragranceName) {
            frag->addQuantity(quantity);
            found = true;

            std::cout << "Successfully added " << quantity
                << " pieces per perfume '" << fragranceName << "'.\n";
            break;
        }
    }

    if (!found) {
        std::cout << "Perfume with a name '" << fragranceName << "' does not exist in the catalog.\n";
    }
}

bool NotinoOOP::deliverPurchase(int purchaseId) {
    for (auto& purchase : purchases) {
        if (purchase.getPurchaseId() == purchaseId) {
            // Only an order that is being processed (PENDING) can be delivered.
            if (purchase.getStatus() == PurchaseStatus::PENDING) {
                purchase.setStatus(PurchaseStatus::DELIVERED);

                return true;
            }

            break; // Found it, but the status is not PENDING.
        }
    }

    return false;
}

bool NotinoOOP::removeReviewAndPenalize(int fragranceId, int reviewId) {
    auto frag = fragranceRepo.findById(fragranceId);
    if (!frag) {
        return false;
    }

    int targetUserId = -1;
    for (auto it = reviews.begin(); it != reviews.end(); it++) {
        if (it->getId() == reviewId) {
            targetUserId = it->getUserId();
            reviews.erase(it);

            break;
        }
    }

    if (targetUserId == -1) {
        return false;
    }

    // Deleting the review from the list of the perfume itself
    frag->removeReviewById(reviewId);

    // Looking for the author among the users to punish them.
    for (const auto& user : userRepo.getAll()) {
        if (user && user->getId() == targetUserId) {

            if (!user->isAdmin()) {
                user->applyReviewPenalty();

                if (user->shouldBeBlocked()) {
                    std::cout << "The user '" << user->getUsername()
                        << "' has 7+ removed reviews and is automatically blocked!\n";

                    blockUser(user->getUsername());
                }
            }

            break;
        }
    }

    return true;
}

bool NotinoOOP::addReviewToFragrance(const std::string& fragName, int userId, int rating, const std::string& comment) {
    auto frag = findFragranceByName(fragName);
    if (!frag) {
        std::cout << "Error! Perfume with name '" << fragName << "' does not exist in the catalog.\n";

        return false;
    }

    int newReviewId = reviews.empty() ? 1 : reviews.back().getId() + 1;
    Review newReview(newReviewId, fragName, userId, comment, rating);

    reviews.push_back(newReview);
    frag->addReview(newReview);

    return true;
}

bool NotinoOOP::cancelPurchase(int purchaseId) {
    if (!currentUser) {
        return false;
    }

    for (auto& purchase : purchases) {
        if (purchase.getPurchaseId() == purchaseId) {
            if (purchase.getUserId() != currentUser->getId()) {
                std::cout << "Error! This order does not belong to you.\n";

                return false;
            }

            if (purchase.getStatus() != PurchaseStatus::PENDING) {
                std::cout << "Error! You can only cancel orders that are in the process of being processed (PENDING).\n";

                return false;
            }

            bool isRefunded = false;
            BuyerActionVisitor visitor([&purchase, &isRefunded](Buyer& buyer) {

                // Returning the money to buyer
                double refundAmount = purchase.calculateTotalPrice();
                buyer.addToBalance(refundAmount);

                // Restoring the quantities
                for (const auto& purchaseItem : purchase.getItems()) {
                    if (purchaseItem.fragrance) {
                        purchaseItem.fragrance->addQuantity(1);
                    }
                }

                isRefunded = true;
                });

            currentUser->acceptModifier(visitor);
            if (isRefunded) {
                purchase.setStatus(PurchaseStatus::CANCELED);

                return true;
            }
            else {
                return false;
            }
        }
    }

    std::cout << "Error! Order with ID #" << purchaseId << " was not found.\n";

    return false;
}