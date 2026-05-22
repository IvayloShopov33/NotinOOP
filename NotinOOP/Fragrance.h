#pragma once
#include <string>
#include <vector>

#include "Review.h"

class Fragrance {
private:
    static int nextId;

    int id;
    std::string name;
    std::string brand;

    double price;
    int quantity;

    std::vector<std::string> fragranceFamily;
    std::vector<Review> reviews;

    void initialize(const std::string& name, const std::string& brand, double price,
        const std::vector<std::string>& fragranceFamily, int quantity);

public:
    Fragrance(const std::string& name, const std::string& brand, double price,
        const std::vector<std::string>& fragranceFamily, int quantity);

    Fragrance(int id, const std::string& name, const std::string& brand, double price,
        const std::vector<std::string>& fragranceFamily, int quantity);

    int getId() const;
    const std::string& getName() const;
    const std::string& getBrand() const;

    double getPrice() const;
    int getQuantity() const;

    const std::vector<std::string>& getfragranceFamily() const;
    const std::vector<Review>& getReviews() const;

    void addQuantity(int amount);
    void reduceQuantity(int amount);

    void addReview(const Review& review);
    bool removeReviewById(int reviewId);

    double getRating() const;
};