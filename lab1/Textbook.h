#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "Base.h"

class Textbook : public Base {
public:
    Textbook();
    Textbook(const std::string& title, const std::string& author, int year,
             const std::string& institution, int studyYear, int pages, double price);
    Textbook(const Textbook& other);
    ~Textbook() override;

    Textbook& operator=(const Textbook& other);

    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    const std::string& getInstitution() const;
    int getStudyYear() const;
    int getPages() const;

    void setTitle(const std::string& value);
    void setAuthor(const std::string& value);
    void setYear(int value);
    void setInstitution(const std::string& value);
    void setStudyYear(int value);
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
    std::string institution;
    int studyYear;
    int pages;
};

#endif
