#pragma once
#include <string>

class Review {
private:
    static int nextId;

    int id;
    std::string fragranceName;
    int userId;
    std::string comment;
    int rating;

    void initialize(const std::string& fragranceName, int userId, const std::string& comment, int rating);

public:
    Review(const std::string& fragranceName, int userId, const std::string& comment, int rating);
    Review(int id, const std::string& fragranceName, int userId, const std::string& comment, int rating);

    int getId() const;
    const std::string& getFragranceName() const;
    int getUserId() const;
    const std::string& getComment() const;
    int getRating() const;
};