#pragma once
#include <vector>
#include <memory>
#include "Fragrance.h"

class FragranceRepository {
private:
    std::vector<std::shared_ptr<Fragrance>> fragrances;

public:
    void addFragrance(std::shared_ptr<Fragrance> fragrance);

    std::shared_ptr<Fragrance> findById(int id) const;

    bool removeFragrance(int id);

    const std::vector<std::shared_ptr<Fragrance>>& getAll() const;
};