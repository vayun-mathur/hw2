#include "book.h"
#include "util.h"

Book::Book(const std::string name, double price, int qty, const std::string isbn, const std::string author) : Product("book", name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

Book::~Book()
{
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> author = parseStringToWords(author_);
    keywords = setUnion(name, author);
    keywords.insert(isbn_);
    return keywords;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

std::string Book::displayString() const
{
    std::string display;
    std::string price = std::to_string(price_);
    std::string qty = std::to_string(qty_);
    display = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n" + price + " " + qty + " left.";
    return display;
}

void Book::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << isbn_ << std::endl;
    os << author_ << std::endl;
}

std::string Book::getIsbn() const
{
    return isbn_;
}

std::string Book::getAuthor() const
{
    return author_;
}