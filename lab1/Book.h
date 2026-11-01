#ifndef BOOK_H
#define BOOK_H

#include "Base.h"

class Book : public Base {
public:
    Book();
    Book(const std::string& title, const std::string& author, int year,
         const std::string& annotation, const std::string& genre, int pages, double price);
    Book(const Book& other);
    ~Book() override;

    Book& operator=(const Book& other);

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    const std::string& getAnnotation() const;
    const std::string& getGenre() const;
    int getPages() const;

    void setTitle(const std::string& value);
    void setAuthor(const std::string& value);
    void setYear(int value);
    void setAnnotation(const std::string& value);
    void setGenre(const std::string& value);
    void setPages(int value);

    Base* clone() const override;
    std::string typeName() const override;
    void print(std::ostream& out) const override;
    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

private:
    std::string title;
    std::string author;
    int year;
    std::string annotation;
    std::string genre;
    int pages;
};

#endif
