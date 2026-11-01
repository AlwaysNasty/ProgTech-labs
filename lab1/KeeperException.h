#ifndef KEEPER_EXCEPTION_H
#define KEEPER_EXCEPTION_H

#include <exception>
#include <string>

// Исключение программы; текст поясняет возникшую ситуацию
class KeeperException : public std::exception {
public:
    explicit KeeperException(const std::string& message);
    const char* what() const noexcept override;

private:
    std::string message;
};

#endif
