#include <algorithm>
#include <vector>

#include "FragranceRepository.h"

void FragranceRepository::addFragrance(std::shared_ptr<Fragrance> fragrance) {
    if (fragrance) {
        fragrances.push_back(std::move(fragrance));
    }
}

std::shared_ptr<Fragrance> FragranceRepository::findById(int id) const {
    auto it = std::find_if(fragrances.begin(), fragrances.end(),
        [id](const std::shared_ptr<Fragrance>& fragrance) {
            return fragrance->getId() == id;
        });

    if (it != fragrances.end()) {
        return *it;
    }

    return nullptr;
}

bool FragranceRepository::removeFragrance(int id) {
    size_t removedCount = std::erase_if(fragrances, [id](const std::shared_ptr<Fragrance>& fragrance) {
        return fragrance->getId() == id;
        });

    return removedCount > 0;
}

const std::vector<std::shared_ptr<Fragrance>>& FragranceRepository::getAll() const {
    return fragrances;
}