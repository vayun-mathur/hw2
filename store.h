#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    virtual ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    virtual void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */

    virtual void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    virtual std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */

    virtual void dump(std::ostream& ofile);

    /**
     * Adds a product to a user's cart
     */
    void addCart(std::string username, Product* p);

    /**
     * Returns the cart of a user
     */
    std::queue<Product*> viewCart(std::string username);

    /**
     * Buys all the products in a user's cart
     */
    void buyCart(std::string username);

private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<User*, std::queue<Product*> > cart_;
};