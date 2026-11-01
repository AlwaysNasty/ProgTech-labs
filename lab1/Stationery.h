#ifndef STATIONERY_H
#define STATIONERY_H

#include "Base.h"

class Stationery : public Base {
public:
    Stationery();
    Stationery(const std::string& type, const std::string& color,
               const std::string& purpose, double price);
    Stationery(const Stationery& other);
    ~Stationery() override;

    Stationery& operator=(const Stationery& other);

    const std::string& getType() const;
    const std::string& getColor() const;
    const std::string& getPurpose() const;

    void setType(const std::string& value);
    void setColor(const std::string& value);
    void setPurpose(const std::string& value);

    Base* clone() const override;
    std::string typeName() const override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

private:
    std::string type;
    std::string color;
    std::string purpose;
};

#endif
