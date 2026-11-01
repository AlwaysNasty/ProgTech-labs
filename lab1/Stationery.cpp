#include "Stationery.h"

Stationery::Stationery() {
    std::cout << "[Stationery] конструктор без параметров\n";
}

Stationery::Stationery(const std::string& type, const std::string& color,
                       const std::string& purpose, double price)
    : Base(price) {
    setType(type);
    setColor(color);
    setPurpose(purpose);
    std::cout << "[Stationery] конструктор с параметрами: \"" << this->type << "\"\n";
}

Stationery::Stationery(const Stationery& other)
    : Base(other), type(other.type), color(other.color), purpose(other.purpose) {
    std::cout << "[Stationery] конструктор копирования: \"" << type << "\"\n";
}

Stationery::~Stationery() {
    std::cout << "[Stationery] деструктор: \"" << type << "\"\n";
}

Stationery& Stationery::operator=(const Stationery& other) {
    if (this != &other) {
        Base::operator=(other);
        type = other.type;
        color = other.color;
        purpose = other.purpose;
    }
    return *this;
}

const std::string& Stationery::getType() const { return type; }
const std::string& Stationery::getColor() const { return color; }
const std::string& Stationery::getPurpose() const { return purpose; }

void Stationery::setType(const std::string& value) { type = checkText(value, "Тип канцелярии"); }
void Stationery::setColor(const std::string& value) { color = checkText(value, "Цвет"); }
void Stationery::setPurpose(const std::string& value) { purpose = checkText(value, "Назначение"); }

Base* Stationery::clone() const {
    return new Stationery(*this);
}

std::string Stationery::typeName() const {
    return "Stationery";
}

void Stationery::print(std::ostream& out) const {
    out << "Канцелярия: \"" << type << "\", цвет: " << color
        << ", назначение: " << purpose << ", стоимость: " << getPrice();
}

void Stationery::save(std::ostream& out) const {
    out << type << '\n' << color << '\n' << purpose << '\n';
    writeDouble(out, getPrice());
}

void Stationery::load(std::istream& in) {
    setType(readLine(in));
    setColor(readLine(in));
    setPurpose(readLine(in));
    setPrice(readDouble(in));
}
