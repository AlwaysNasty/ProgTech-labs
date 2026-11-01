#include "Base.h"

#include <cmath>
#include <iomanip>
#include <limits>
#include <stdexcept>

#include "KeeperException.h"

Base::Base() : price(0) {
    std::cout << "[Base] конструктор без параметров\n";
}

Base::Base(double price) : price(0) {
    setPrice(price);
    std::cout << "[Base] конструктор с параметрами\n";
}

Base::Base(const Base& other) : price(other.price) {
    std::cout << "[Base] конструктор копирования\n";
}

Base::~Base() {
    std::cout << "[Base] деструктор\n";
}

Base& Base::operator=(const Base& other) {
    price = other.price;
    return *this;
}

double Base::getPrice() const {
    return price;
}

void Base::setPrice(double value) {
    if (!std::isfinite(value) || value < 0) {
        throw KeeperException("Стоимость должна быть неотрицательным числом");
    }
    price = value;
}

std::string Base::checkText(const std::string& value, const std::string& field) {
    if (value.empty()) {
        throw KeeperException("Поле \"" + field + "\" не может быть пустым");
    }
    return value;
}

std::string Base::readLine(std::istream& in) {
    std::string line;
    if (!std::getline(in, line)) {
        throw KeeperException("Файл повреждён: данные закончились раньше времени");
    }
    return line;
}

int Base::readInt(std::istream& in) {
    const std::string line = readLine(in);
    try {
        std::size_t used = 0;
        const int value = std::stoi(line, &used);
        if (used == line.size()) {
            return value;
        }
    } catch (const std::logic_error&) {
    }
    throw KeeperException("Файл повреждён: ожидалось целое число, получено \"" + line + "\"");
}

double Base::readDouble(std::istream& in) {
    const std::string line = readLine(in);
    try {
        std::size_t used = 0;
        const double value = std::stod(line, &used);
        if (used == line.size()) {
            return value;
        }
    } catch (const std::logic_error&) {
    }
    throw KeeperException("Файл повреждён: ожидалось число, получено \"" + line + "\"");
}

void Base::writeDouble(std::ostream& out, double value) {
    out << std::setprecision(std::numeric_limits<double>::max_digits10) << value << '\n';
}

std::ostream& operator<<(std::ostream& out, const Base& item) {
    item.print(out);
    return out;
}
