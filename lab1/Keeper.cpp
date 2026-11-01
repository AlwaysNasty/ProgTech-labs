#include "Keeper.h"

#include <fstream>
#include <utility>

#include "Book.h"
#include "KeeperException.h"
#include "Stationery.h"
#include "Textbook.h"

namespace {
const char* const FILE_HEADER = "KEEPER";

Base* createItem(const std::string& typeName) {
    if (typeName == "Book") {
        return new Book();
    }
    if (typeName == "Textbook") {
        return new Textbook();
    }
    if (typeName == "Stationery") {
        return new Stationery();
    }
    throw KeeperException("Файл повреждён: неизвестный тип объекта \"" + typeName + "\"");
}
}

Keeper::Keeper() : items(nullptr), size(0), capacity(0) {
    std::cout << "[Keeper] конструктор без параметров\n";
}

Keeper::Keeper(int capacity) : items(nullptr), size(0), capacity(0) {
    if (capacity < 0) {
        throw KeeperException("Вместимость контейнера не может быть отрицательной");
    }
    items = new Base*[capacity];
    this->capacity = capacity;
    std::cout << "[Keeper] конструктор с параметрами: вместимость " << capacity << "\n";
}

Keeper::Keeper(const Keeper& other) : items(nullptr), size(0), capacity(0) {
    items = new Base*[other.capacity];
    capacity = other.capacity;
    try {
        for (int i = 0; i < other.size; ++i) {
            items[i] = other.items[i]->clone();
            ++size;
        }
    } catch (...) {
        clear();
        throw;
    }
    std::cout << "[Keeper] конструктор копирования: объектов " << size << "\n";
}

Keeper::~Keeper() {
    std::cout << "[Keeper] деструктор: объектов " << size << "\n";
    clear();
}

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        std::swap(items, copy.items);
        std::swap(size, copy.size);
        std::swap(capacity, copy.capacity);
    }
    return *this;
}

Keeper& Keeper::operator+=(Base* item) {
    if (item == nullptr) {
        throw KeeperException("Нельзя добавить пустой объект");
    }
    if (size == capacity) {
        grow();
    }
    items[size++] = item;
    return *this;
}

Keeper& Keeper::operator-=(int index) {
    checkIndex(index);
    delete items[index];
    for (int i = index; i < size - 1; ++i) {
        items[i] = items[i + 1];
    }
    --size;
    return *this;
}

Base& Keeper::operator[](int index) {
    checkIndex(index);
    return *items[index];
}

const Base& Keeper::operator[](int index) const {
    checkIndex(index);
    return *items[index];
}

int Keeper::getSize() const {
    return size;
}

int Keeper::getCapacity() const {
    return capacity;
}

void Keeper::save(const std::string& fileName) const {
    std::ofstream file(fileName);
    if (!file) {
        throw KeeperException("Не удалось открыть файл для записи: " + fileName);
    }
    file << FILE_HEADER << '\n' << size << '\n';
    for (int i = 0; i < size; ++i) {
        file << items[i]->typeName() << '\n';
        items[i]->save(file);
    }
    file.flush();
    if (!file) {
        throw KeeperException("Ошибка записи в файл: " + fileName);
    }
}

void Keeper::load(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file) {
        throw KeeperException("Не удалось открыть файл для чтения: " + fileName);
    }

    std::string header;
    if (!std::getline(file, header) || header != FILE_HEADER) {
        throw KeeperException("Файл не является сохранением магазина: " + fileName);
    }
    int count = 0;
    if (!(file >> count) || count < 0) {
        throw KeeperException("Файл повреждён: неверное количество объектов");
    }
    file.ignore(1);

    // Текущие данные заменяются, только если весь файл прочитан без ошибок
    Keeper loaded(count);
    for (int i = 0; i < count; ++i) {
        std::string typeName;
        if (!std::getline(file, typeName)) {
            throw KeeperException("Файл повреждён: объектов меньше, чем заявлено");
        }
        Base* item = createItem(typeName);
        try {
            item->load(file);
        } catch (...) {
            delete item;
            throw;
        }
        loaded += item;
    }
    *this = loaded;
}

void Keeper::clear() {
    for (int i = 0; i < size; ++i) {
        delete items[i];
    }
    delete[] items;
    items = nullptr;
    size = 0;
    capacity = 0;
}

void Keeper::grow() {
    const int newCapacity = capacity == 0 ? 4 : capacity * 2;
    Base** newItems = new Base*[newCapacity];
    for (int i = 0; i < size; ++i) {
        newItems[i] = items[i];
    }
    delete[] items;
    items = newItems;
    capacity = newCapacity;
}

void Keeper::checkIndex(int index) const {
    if (index < 0 || index >= size) {
        throw KeeperException("Нет объекта с номером " + std::to_string(index + 1));
    }
}

std::ostream& operator<<(std::ostream& out, const Keeper& keeper) {
    if (keeper.getSize() == 0) {
        return out << "Магазин пуст\n";
    }
    for (int i = 0; i < keeper.getSize(); ++i) {
        out << i + 1 << ". " << keeper[i] << '\n';
    }
    return out;
}
