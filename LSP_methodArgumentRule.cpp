#include <iostream>
using namespace std;

// Signature rule: Method Argument Rule, Return type rule, Exception rule
//  Subtype method arguments should be the identical or wider than the supertype method arguments
//  C++ imposes this by keeping signature identical in derived classes

class Parent
{
public:
    virtual void print(string msg)
    {
        cout << "Parent: " << msg << endl;
    }
};

class Child : public Parent
{
public:
    void print(string msg) override
    {
        cout << "Child: " << msg << endl;
    }
};

class Client
{
private:
    Parent *p;

public:
    Client(Parent *p)
    {
        this->p = p;
    }
    void printMsg()
    {
        p->print("Hello LSP");
    }
};

int main()
{
    Parent *parent = new Parent();
    Parent *child = new Child();

    // Client *client = new Client(parent)
    Client *client = new Client(child);

    client->printMsg();
}