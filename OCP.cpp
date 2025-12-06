#include <iostream>
#include <vector>
using namespace std;

class Product
{
public:
    string name;
    double price;
    Product(string name, double price)
    {
        this->name = name;
        this->price = price;
    }
};

// SRP followed: ShoppingCart holds only 1 responsibility
class ShoppingCart
{
private:
    vector<Product *> products;

public:
    void addProduct(Product *p)
    {
        products.push_back(p);
    }
    const vector<Product *> &getProducts()
    {
        return products;
    }
    double calcTotalPrice()
    {
        double total = 0;
        for (auto p : products)
        {
            total += p->price;
        }
        return total;
    }
};
class ShoppingCartPrinter
{
private:
    ShoppingCart *cart;

public:
    ShoppingCartPrinter(ShoppingCart *cart)
    {
        this->cart = cart;
    }
    void printInvoice()
    {
        cout << "Shopping Cart Invoice:\n";
        for (auto p : cart->getProducts())
        {
            cout << p->name << " : $" << p->price << "\n";
        }
        cout << "Total Price: $" << cart->calcTotalPrice() << endl;
    }
};

// // OCP violated: Adding new storage types requires modifying this class
// class ShoppingCartStorageinDB
// {
// private:
//     ShoppingCart *cart;

// public:
//     ShoppingCartStorageinDB(ShoppingCart *cart)
//     {
//         this->cart = cart;
//     }
//     void saveToSQLDB()
//     {
//         cout << "Saving the shopping cart to SQL DB.." << endl;
//     }
//     void saveToMongoDB()
//     {
//         cout << "Saving the shopping cart to MongoDB.." << endl;
//     }
//     void saveToFile()
//     {
//         cout << "Saving the shopping cart to File.." << endl;
//     }
// };

// OCP followed: Each storage type has its own class

// Abstract base class
class ShoppingCartStorageinDB
{
private:
    ShoppingCart *cart;

public:
    virtual void saveToDB(ShoppingCart *cart) = 0; // pure virtual fn
};
// SQL storage class
class storeToSQLDB : public ShoppingCartStorageinDB
{
public:
    void saveToDB(ShoppingCart *cart) override
    {
        cout << "Saving the shopping cart to SQL DB.." << endl;
    }
};
// MongoDB storage class
class storeToMongoDB : public ShoppingCartStorageinDB
{
public:
    void saveToDB(ShoppingCart *cart) override
    {
        cout << "Saving the shopping cart to MongoDB.." << endl;
    }
};
// File storage class
class storeToFile : public ShoppingCartStorageinDB
{
public:
    void saveToDB(ShoppingCart *cart) override
    {
        cout << "Saving the shopping cart to File.." << endl;
    }
};

int main()
{
    ShoppingCart *cart = new ShoppingCart();
    cart->addProduct(new Product("Book", 11.79));
    cart->addProduct(new Product("Mouse", 15.49));

    ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorageinDB *store1 = new storeToSQLDB();
    store1->saveToDB(cart);
    ShoppingCartStorageinDB *store2 = new storeToMongoDB();
    store2->saveToDB(cart);
    ShoppingCartStorageinDB *store3 = new storeToFile();
    store3->saveToDB(cart);

    return 0;
}
