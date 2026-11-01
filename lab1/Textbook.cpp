#include "Textbook.h"

#include "KeeperException.h"

Textbook::Textbook() : year(0), studyYear(0), pages(0) {
    std::cout << "[Textbook] конструктор без параметров\n";
}

Textbook::Textbook(const std::string& title, const std::string& author, int year,
                   const std::string& institution, int studyYear, int pages, double price)
    : Base(price), year(0), studyYear(0), pages(0) {
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setInstitution(institution);
    setStudyYear(studyYear);
    setPages(pages);
    std::cout << "[Textbook] конструктор с параметрами: \"" << this->title << "\"\n";
}

Textbook::Textbook(const Textbook& other)
    : Base(other), title(other.title), author(other.author), year(other.year),
      institution(other.institution), studyYear(other.studyYear), pages(other.pages) {
    std::cout << "[Textbook] конструктор копирования: \"" << title << "\"\n";
}

Textbook::~Textbook() {
    std::cout << "[Textbook] деструктор: \"" << title << "\"\n";
}

Textbook& Textbook::operator=(const Textbook& other) {
    if (this != &other) {
        Base::operator=(other);
        title = other.title;
        author = other.author;
        year = other.year;
        institution = other.institution;
        studyYear = other.studyYear;
        pages = other.pages;
    }
    return *this;
}

const std::string& Textbook::getTitle() const { return title; }
const std::string& Textbook::getAuthor() const { return author; }
int Textbook::getYear() const { return year; }
const std::string& Textbook::getInstitution() const { return institution; }
int Textbook::getStudyYear() const { return studyYear; }
int Textbook::getPages() const { return pages; }

void Textbook::setTitle(const std::string& value) { title = checkText(value, "Название"); }
void Textbook::setAuthor(const std::string& value) { author = checkText(value, "Автор"); }

void Textbook::setYear(int value) {
    if (value <= 0) {
        throw KeeperException("Год выпуска должен быть положительным");
    }
    year = value;
}

void Textbook::setInstitution(const std::string& value) {
    institution = checkText(value, "Учебное заведение");
}

void Textbook::setStudyYear(int value) {
    if (value <= 0) {
        throw KeeperException("Год обучения должен быть положительным");
    }
    studyYear = value;
}

void Textbook::setPages(int value) {
    if (value <= 0) {
        throw KeeperException("Объём страниц должен быть положительным");
    }
    pages = value;
}

Base* Textbook::clone() const {
    return new Textbook(*this);
}

std::string Textbook::typeName() const {
    return "Textbook";
}

void Textbook::print(std::ostream& out) const {
    out << "Учебник: \"" << title << "\", автор: " << author << ", год: " << year
        << ", учебное заведение: " << institution << ", год обучения: " << studyYear
        << ", страниц: " << pages << ", стоимость: " << getPrice();
}

void Textbook::save(std::ostream& out) const {
    out << title << '\n' << author << '\n' << year << '\n' << institution << '\n'
        << studyYear << '\n' << pages << '\n';
    writeDouble(out, getPrice());
}

void Textbook::load(std::istream& in) {
    setTitle(readLine(in));
    setAuthor(readLine(in));
    setYear(readInt(in));
    setInstitution(readLine(in));
    setStudyYear(readInt(in));
    setPages(readInt(in));
    setPrice(readDouble(in));
}
