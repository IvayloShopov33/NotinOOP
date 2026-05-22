#include <stdexcept>

#include "Fragrance.h"
#include "FragranceValidator.h"
#include "TextValidator.h"

int Fragrance::nextId = 0;

void Fragrance::initialize(const std::string& name, const std::string& brand, double price,
    const std::vector<std::string>& fragranceFamily, int quantity) {
    TextValidator::validateName(name, "Fragrance name");
    TextValidator::validateName(brand, "Fragrance brand");

    FragranceValidator::validatePrice(price);
    FragranceValidator::validateQuantity(quantity);

    for (const auto& note : fragranceFamily) {
        TextValidator::validateName(note, "Fragrance family");
    }

    this->name = name;
    this->brand = brand;
    this->price = price;
    this->fragranceFamily = fragranceFamily;
    this->quantity = quantity;
}

Fragrance::Fragrance(const std::string& name, const std::string& brand, double price,
    const std::vector<std::string>& fragranceFamily, int quantity) {
	initialize(name, brand, price, fragranceFamily, quantity);

    this->id = ++nextId;
}

Fragrance::Fragrance(int existingId, const std::string& name, const std::string& brand, double price,
    const std::vector<std::string>& fragranceFamily, int quantity) {
	initialize(name, brand, price, fragranceFamily, quantity);

    this->id = existingId;
    if (existingId >= nextId) {
        nextId = existingId + 1;
    }
}

int Fragrance::getId() const { return id; }
const std::string& Fragrance::getName() const { return name; }
const std::string& Fragrance::getBrand() const { return brand; }

double Fragrance::getPrice() const { return price; }
int Fragrance::getQuantity() const { return quantity; }

const std::vector<std::string>& Fragrance::getfragranceFamily() const { return fragranceFamily; }
const std::vector<Review>& Fragrance::getReviews() const { return reviews; }

void Fragrance::addQuantity(int amount) {
    FragranceValidator::validateAmount(amount);
    quantity += amount;
}

void Fragrance::reduceQuantity(int amount) {
    FragranceValidator::validateAmount(amount);
	FragranceValidator::validateSufficientQuantity(amount, quantity);

    quantity -= amount;
}

void Fragrance::addReview(const Review& review) {
    reviews.push_back(review);
}

bool Fragrance::removeReviewById(int reviewId) {
    for (auto it = reviews.begin(); it != reviews.end(); ++it) {
        if (it->getId() == reviewId) {
            reviews.erase(it);
            return true;
        }
    }

    return false;
}

double Fragrance::getRating() const {
    if (reviews.empty()) {
        return 0.0; 
    }

    double sum = 0.0;
    for (const auto& review : reviews) {
        sum += review.getRating();
    }

    return sum / reviews.size();
}