#ifndef KEEPER_H
#define KEEPER_H

#include <iostream>
#include <string>

#include "Base.h"

// Контейнер товаров книжного магазина на динамическом массиве указателей
class Keeper {
public:
    Keeper();
    explicit Keeper(int capacity);
    Keeper(const Keeper& other);
    ~Keeper();

    Keeper& operator=(const Keeper& other);
    Keeper& operator+=(Base* item);  // забирает владение объектом
    Keeper& operator-=(int index);
    Base& operator[](int index);
    const Base& operator[](int index) const;

    int getSize() const;
    int getCapacity() const;

    void save(const std::string& fileName) const;
    void load(const std::string& fileName);

private:
    void clear();
    void grow();
    void checkIndex(int index) const;

    Base** items;
    int size;
    int capacity;
};

std::ostream& operator<<(std::ostream& out, const Keeper& keeper);

#endif
