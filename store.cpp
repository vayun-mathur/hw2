#include "store.h"
#include "util.h"

MyDataStore::MyDataStore()
{
}

MyDataStore::~MyDataStore()
{
    for (unsigned int i = 0; i < products_.size(); i++)
    {
        delete products_[i];
    }
    for (auto&& [_, u] : users_)
    {
        delete u;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.push_back(p);
}

void MyDataStore::addUser(User* u)
{
    users_.insert({u->getName(), u});
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::vector<Product*> hits;
    std::set<Product*> hitsSet;
    std::set<Product*> total;
    std::set<std::string> termsSet;
    if (type == 0)
    {
        for (unsigned int i = 0; i < terms.size(); i++)
        {
            hitsSet.clear();
            std::string term = terms[i];
            for( unsigned int j = 0; j < products_.size(); j++) { 
                std::set<std::string> keywords = products_[j]->keywords();
                if (keywords.find(term) != keywords.end())
                {
                    hitsSet.insert(products_[j]);
                }
            }
            if(i == 0) {
                total = hitsSet;
            }
            else {
                total = setIntersection(total, hitsSet);
            }
        }
    }
    else if (type == 1)
    {
        for (unsigned int i = 0; i < terms.size(); i++)
        {
            hitsSet.clear();
            std::string term = terms[i];
            for( unsigned int j = 0; j < products_.size(); j++) { 
                std::set<std::string> keywords = products_[j]->keywords();
                if (keywords.find(term) != keywords.end())
                {
                    hitsSet.insert(products_[j]);
                }
            }
            if(i == 0) {
                total = hitsSet;
            }
            else {
                total = setUnion(total, hitsSet);
            }
        }
    }
    for (std::set<Product*>::iterator it = total.begin(); it != total.end(); ++it)
    {
        hits.push_back(*it);
    }
    return hits;
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    for (unsigned int i = 0; i < products_.size(); i++)
    {
        products_[i]->dump(ofile);
    }
    ofile << "</products>" << std::endl;
    ofile << "<users>" << std::endl;
    for (auto&& [_, u] : users_)
    {
        u->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}

void MyDataStore::addCart(std::string username, Product* p)
{
    if(users_.find(username) == users_.end())
    {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    cart_[users_[username]].push(p);
}

std::queue<Product*> MyDataStore::viewCart(std::string username)
{
    if(users_.find(username) == users_.end())
    {
        std::cout << "Invalid username" << std::endl;
        return std::queue<Product*>();
    }
    return cart_[users_[username]];
}

void MyDataStore::buyCart(std::string username)
{

    if(users_.find(username) == users_.end())
    {
        std::cout << "Invalid username" << std::endl;
        return;
    }

    std::queue<Product*>& cart = cart_[users_[username]];
    while(!cart.empty())
    {
        if (users_[username]->getBalance() >= cart.front()->getPrice() && cart.front()->getQty() > 0)
        {
            users_[username]->deductAmount(cart.front()->getPrice());
            cart.front()->subtractQty(1);
            cart.pop();
        }
        else
        {
            std::cout << "Insufficient funds" << std::endl;
            break;
        }
    }
}