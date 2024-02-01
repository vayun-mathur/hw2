#include "movie.h"
#include "util.h"

Movie::Movie(const std::string name, double price, int qty, const std::string genre, const std::string rating) : Product("movie", name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie()
{
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> genre = parseStringToWords(genre_);
    keywords = setUnion(name, genre);
    return keywords;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

std::string Movie::displayString() const
{
    std::string display;
    std::string price = std::to_string(price_);
    std::string qty = std::to_string(qty_);
    display = name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n" + price + " " + qty + " left.";
    return display;
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}

std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}