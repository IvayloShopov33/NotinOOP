#pragma once
#include <stdexcept>
#include <string>

class CommandParseException : public std::invalid_argument {
public:
    explicit CommandParseException(const std::string& message);
};