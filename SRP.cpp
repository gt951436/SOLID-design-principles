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

// SRP violation: ShoppingCart holds multiple responsibilities
// class ShoppingCart
// {
// private:
//     vector<Product *> products;

// public:
//     void addProduct(Product *p)
//     {
//         products.push_back(p);
//     }
//     const vector<Product *> &getProducts()
//     {
//         return products;
//     }
//     double calcTotalPrice()
//     {
//         double total = 0;
//         for (auto p : products)
//         {
//             total += p->price;
//         }
//         return total;
//     }
//     void printInvoice()
//     {
//         cout << "Shopping Cart Invoice:\n";
//         for (auto p : products)
//         {
//             cout << p->name << " : $" << p->price << "\n";
//         }
//     }
//     void saveToDB()
//     {
//         cout << "Saving the shopping cart to database.." << endl;
//     }
// };

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
class ShoppingCartStorageinDB
{
private:
    ShoppingCart *cart;

public:
    ShoppingCartStorageinDB(ShoppingCart *cart)
    {
        this->cart = cart;
    }
    void saveToDB()
    {
        cout << "Saving the shopping cart to database.." << endl;
    }
};

int main()
{
    ShoppingCart *cart = new ShoppingCart();
    cart->addProduct(new Product("Book", 11.79));
    cart->addProduct(new Product("Mouse", 15.49));

    ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorageinDB *store = new ShoppingCartStorageinDB(cart);
    store->saveToDB();

    return 0; 
}
