#pragma once
#include <functional>
#include <vector>
#include <memory>
#include <string>
#include <iostream>

#include "UserRepository.h"
#include "FragranceRepository.h"
#include "DiscountRepository.h"
#include "Purchase.h"
#include "User.h"

class NotinoOOP {
private:
	const std::string DATABASE_FILE = "system_data.txt";

	UserRepository userRepo;
	FragranceRepository fragranceRepo;
	DiscountRepository discountRepo;

	std::vector<Purchase> purchases;
	std::vector<Review> reviews;
	std::shared_ptr<User> currentUser;

public:
	NotinoOOP();
	~NotinoOOP() = default;

	void loadData();
	void saveData() const;

	bool registerUser(const std::string& username, const std::string& password);
	bool registerAdmin(const std::string& username, const std::string& password);

	bool loginUser(const std::string& username, const std::string& password);
	void logoutUser();
	std::shared_ptr<User> getCurrentUser() const;

	void addFragranceToCatalog(std::shared_ptr<Fragrance> fragrance);
	bool removeFragranceFromCatalog(int fragranceId);
	std::shared_ptr<Fragrance> findFragranceByName(const std::string& name) const;
	void addDiscountToSystem(std::shared_ptr<Discount> discount);

	void showCatalog(std::ostream& os = std::cout) const;
	bool checkout();

	void showPurchasesFiltered(std::function<bool(const Purchase&)> filter, std::ostream& os = std::cout) const;
	void showCurrentUserPurchaseHistory(std::ostream& os = std::cout) const;
	void showCurrentUserDeliveredPurchases(std::ostream& os = std::cout) const;
	void showAllPurchasesInSystem(std::ostream& os = std::cout) const;

	bool blockUser(const std::string& username);
	void addQuantityToFragrance(const std::string& fragranceName, int quantity);
	bool deliverPurchase(int purchaseId);
	bool removeReviewAndPenalize(int fragranceId, int reviewId);

	bool addReviewToFragrance(const std::string& fragName, int userId, int rating, const std::string& comment);
	bool cancelPurchase(int purchaseId);

	void recommendFragrances() const;
};