#include "Book.h"

#include "KeeperException.h"

Book::Book() : year(0), pages(0) {
    std::cout << "[Book] конструктор без параметров\n";
}

Book::Book(const std::string& title, const std::string& author, int year,
           const std::string& annotation, const std::string& genre, int pages, double price)
    : Base(price), year(0), pages(0) {
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setAnnotation(annotation);
    setGenre(genre);
    setPages(pages);
    std::cout << "[Book] конструктор с параметрами: \"" << this->title << "\"\n";
}

Book::Book(const Book& other)
    : Base(other), title(other.title), author(other.author), year(other.year),
      annotation(other.annotation), genre(other.genre), pages(other.pages) {
    std::cout << "[Book] конструктор копирования: \"" << title << "\"\n";
}

Book::~Book() {
    std::cout << "[Book] деструктор: \"" << title << "\"\n";
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        Base::operator=(other);
        title = other.title;
        author = other.author;
        year = other.year;
        annotation = other.annotation;
        genre = other.genre;
        pages = other.pages;
    }
    return *this;
}

const std::string& Book::getTitle() const { return title; }
const std::string& Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
const std::string& Book::getAnnotation() const { return annotation; }
const std::string& Book::getGenre() const { return genre; }
int Book::getPages() const { return pages; }

void Book::setTitle(const std::string& value) { title = checkText(value, "Название"); }
void Book::setAuthor(const std::string& value) { author = checkText(value, "Автор"); }

void Book::setYear(int value) {
    if (value <= 0) {
        throw KeeperException("Год выпуска должен быть положительным");
    }
    year = value;
}

void Book::setAnnotation(const std::string& value) { annotation = checkText(value, "Аннотация"); }
void Book::setGenre(const std::string& value) { genre = checkText(value, "Жанр"); }

void Book::setPages(int value) {
    if (value <= 0) {
        throw KeeperException("Объём страниц должен быть положительным");
    }
    pages = value;
}

Base* Book::clone() const {
    return new Book(*this);
}

std::string Book::typeName() const {
    return "Book";
}

void Book::print(std::ostream& out) const {
    out << "Книга: \"" << title << "\", автор: " << author << ", год: " << year
        << ", жанр: " << genre << ", страниц: " << pages << ", стоимость: " << getPrice()
        << "\n  Аннотация: " << annotation;
}

void Book::save(std::ostream& out) const {
    out << title << '\n' << author << '\n' << year << '\n' << annotation << '\n'
        << genre << '\n' << pages << '\n';
    writeDouble(out, getPrice());
}

void Book::load(std::istream& in) {
    setTitle(readLine(in));
    setAuthor(readLine(in));
    setYear(readInt(in));
    setAnnotation(readLine(in));
    setGenre(readLine(in));
    setPages(readInt(in));
    setPrice(readDouble(in));
}
