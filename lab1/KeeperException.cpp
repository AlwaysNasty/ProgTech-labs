#include "KeeperException.h"

KeeperException::KeeperException(const std::string& message) : message(message) {}

const char* KeeperException::what() const noexcept {
    return message.c_str();
}
