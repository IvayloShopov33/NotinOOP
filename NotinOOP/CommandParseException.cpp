#include "CommandParseException.h"

CommandParseException::CommandParseException(const std::string& message)
    : std::invalid_argument(message) {}