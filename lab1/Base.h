#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

// Абстрактный товар книжного магазина; стоимость есть у всех товаров
class Base {
public:
    Base();
    explicit Base(double price);
    Base(const Base& other);
    virtual ~Base();

    Base& operator=(const Base& other);

    double getPrice() const;
    void setPrice(double value);

    virtual Base* clone() const = 0;
    virtual std::string typeName() const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;

protected:
    static std::string checkText(const std::string& value, const std::string& field);
    static std::string readLine(std::istream& in);
    static int readInt(std::istream& in);
    static double readDouble(std::istream& in);
    static void writeDouble(std::ostream& out, double value);

private:
    double price;
};

std::ostream& operator<<(std::ostream& out, const Base& item);

#endif
