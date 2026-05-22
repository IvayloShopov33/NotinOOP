#include "PasswordHasher.h"

// djb2 algorithm for hashing
std::string PasswordHasher::hash(const std::string& password) {
    unsigned long hashValue = 5381;

    for (char c : password) {
        // Bitwise shift: hashValue * 33 + ASCII code of the character
        hashValue = ((hashValue << 5) + hashValue) + c;
    }

    return std::to_string(hashValue);
}