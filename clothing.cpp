#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string name, double price, int qty, const std::string size, const std::string brand) : Product("clothing", name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing()
{
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keywords;
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> brand = parseStringToWords(brand_);
    keywords = setUnion(name, brand);
    return keywords;
}

bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}

std::string Clothing::displayString() const
{
    std::string display;
    std::string price = std::to_string(price_);
    std::string qty = std::to_string(qty_);
    display = name_ + "\n" + "Size: " + size_ + " " + "Brand: " + brand_ + "\n" + price + " " + qty + " left.";
    return display;
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}

std::string Clothing::getSize() const
{
    return size_;
}

std::string Clothing::getBrand() const
{
    return brand_;
}