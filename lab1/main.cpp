#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "Book.h"
#include "Keeper.h"
#include "KeeperException.h"
#include "Stationery.h"
#include "Textbook.h"

namespace {

// Конец ввода (Ctrl+D) завершает программу, а не зацикливает меню
class InputClosed : public std::exception {};

std::string readText(const std::string& prompt) {
    std::cout << prompt << ": ";
    std::string line;
    if (!std::getline(std::cin, line)) {
        throw InputClosed();
    }
    return line;
}

int toInt(const std::string& line) {
    try {
        std::size_t used = 0;
        const int value = std::stoi(line, &used);
        if (used == line.size()) {
            return value;
        }
    } catch (const std::logic_error&) {
    }
    throw KeeperException("Ожидалось целое число, получено \"" + line + "\"");
}

double toDouble(const std::string& line) {
    try {
        std::size_t used = 0;
        const double value = std::stod(line, &used);
        if (used == line.size()) {
            return value;
        }
    } catch (const std::logic_error&) {
    }
    throw KeeperException("Ожидалось число, получено \"" + line + "\"");
}

int readInt(const std::string& prompt) {
    return toInt(readText(prompt));
}

double readDouble(const std::string& prompt) {
    return toDouble(readText(prompt));
}

// При редактировании пустая строка оставляет текущее значение
std::string askNew(const std::string& name, const std::string& current) {
    return readText(name + " [" + current + "]");
}

void addItem(Keeper& keeper) {
    std::cout << "1 - книга, 2 - учебник, 3 - канцелярия\n";
    const int type = readInt("Тип товара");
    Base* item = nullptr;
    if (type == 1) {
        const std::string title = readText("Название");
        const std::string author = readText("Автор");
        const int year = readInt("Год выпуска");
        const std::string annotation = readText("Аннотация");
        const std::string genre = readText("Жанр");
        const int pages = readInt("Объём страниц");
        const double price = readDouble("Стоимость");
        item = new Book(title, author, year, annotation, genre, pages, price);
    } else if (type == 2) {
        const std::string title = readText("Название");
        const std::string author = readText("Автор");
        const int year = readInt("Год выпуска");
        const std::string institution = readText("Учебное заведение");
        const int studyYear = readInt("Год обучения");
        const int pages = readInt("Объём страниц");
        const double price = readDouble("Стоимость");
        item = new Textbook(title, author, year, institution, studyYear, pages, price);
    } else if (type == 3) {
        const std::string kind = readText("Тип канцелярии");
        const std::string color = readText("Цвет");
        const std::string purpose = readText("Назначение");
        const double price = readDouble("Стоимость");
        item = new Stationery(kind, color, purpose, price);
    } else {
        throw KeeperException("Неизвестный тип товара: " + std::to_string(type));
    }
    keeper += item;
    std::cout << "Товар добавлен, всего: " << keeper.getSize() << "\n";
}

void editPrice(Base& item) {
    const std::string value = askNew("Стоимость", std::to_string(item.getPrice()));
    if (!value.empty()) {
        item.setPrice(toDouble(value));
    }
}

void editBook(Book& book) {
    std::string value = askNew("Название", book.getTitle());
    if (!value.empty()) book.setTitle(value);
    value = askNew("Автор", book.getAuthor());
    if (!value.empty()) book.setAuthor(value);
    value = askNew("Год выпуска", std::to_string(book.getYear()));
    if (!value.empty()) book.setYear(toInt(value));
    value = askNew("Аннотация", book.getAnnotation());
    if (!value.empty()) book.setAnnotation(value);
    value = askNew("Жанр", book.getGenre());
    if (!value.empty()) book.setGenre(value);
    value = askNew("Объём страниц", std::to_string(book.getPages()));
    if (!value.empty()) book.setPages(toInt(value));
    editPrice(book);
}

void editTextbook(Textbook& textbook) {
    std::string value = askNew("Название", textbook.getTitle());
    if (!value.empty()) textbook.setTitle(value);
    value = askNew("Автор", textbook.getAuthor());
    if (!value.empty()) textbook.setAuthor(value);
    value = askNew("Год выпуска", std::to_string(textbook.getYear()));
    if (!value.empty()) textbook.setYear(toInt(value));
    value = askNew("Учебное заведение", textbook.getInstitution());
    if (!value.empty()) textbook.setInstitution(value);
    value = askNew("Год обучения", std::to_string(textbook.getStudyYear()));
    if (!value.empty()) textbook.setStudyYear(toInt(value));
    value = askNew("Объём страниц", std::to_string(textbook.getPages()));
    if (!value.empty()) textbook.setPages(toInt(value));
    editPrice(textbook);
}

void editStationery(Stationery& stationery) {
    std::string value = askNew("Тип канцелярии", stationery.getType());
    if (!value.empty()) stationery.setType(value);
    value = askNew("Цвет", stationery.getColor());
    if (!value.empty()) stationery.setColor(value);
    value = askNew("Назначение", stationery.getPurpose());
    if (!value.empty()) stationery.setPurpose(value);
    editPrice(stationery);
}

void editItem(Keeper& keeper) {
    Base& item = keeper[readInt("Номер товара") - 1];
    std::cout << item << "\nПустая строка оставляет значение без изменений\n";
    if (Book* book = dynamic_cast<Book*>(&item)) {
        editBook(*book);
    } else if (Textbook* textbook = dynamic_cast<Textbook*>(&item)) {
        editTextbook(*textbook);
    } else if (Stationery* stationery = dynamic_cast<Stationery*>(&item)) {
        editStationery(*stationery);
    }
    std::cout << "Результат: " << item << "\n";
}

void printMenu() {
    std::cout << "\n=== Книжный магазин ===\n"
              << "1. Добавить товар\n"
              << "2. Удалить товар\n"
              << "3. Показать все товары\n"
              << "4. Показать один товар\n"
              << "5. Изменить товар\n"
              << "6. Сохранить в файл\n"
              << "7. Загрузить из файла\n"
              << "0. Выход\n";
}

}

int main() {
    Keeper keeper;
    bool running = true;
    while (running) {
        printMenu();
        try {
            switch (readInt("Выберите пункт")) {
                case 1:
                    addItem(keeper);
                    break;
                case 2:
                    keeper -= readInt("Номер товара") - 1;
                    std::cout << "Товар удалён\n";
                    break;
                case 3:
                    std::cout << keeper;
                    break;
                case 4:
                    std::cout << keeper[readInt("Номер товара") - 1] << "\n";
                    break;
                case 5:
                    editItem(keeper);
                    break;
                case 6:
                    keeper.save(readText("Имя файла"));
                    std::cout << "Сохранено\n";
                    break;
                case 7:
                    keeper.load(readText("Имя файла"));
                    std::cout << "Загружено объектов: " << keeper.getSize() << "\n";
                    break;
                case 0:
                    running = false;
                    break;
                default:
                    throw KeeperException("В меню нет такого пункта");
            }
        } catch (const InputClosed&) {
            running = false;
        } catch (const std::exception& error) {
            std::cout << "Ошибка: " << error.what() << "\n";
        }
    }
    return 0;
}
