#pragma once
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
	void addDiscountToSystem(std::shared_ptr<Discount> discount);

	void showCatalog(std::ostream& os = std::cout) const;
	bool checkout(const std::vector<int>& fragranceIds, int discountId = -1);
	void showCurrentUserPurchaseHistory(std::ostream& os = std::cout) const;
	void showAllPurchasesInSystem(std::ostream& os = std::cout) const;
};