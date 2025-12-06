#include <iostream>
#include <vector>
using namespace std;

// LSP violated
class Account
{
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class savingsAccount : public Account
{
private:
    double balance;

public:
    savingsAccount()
    {
        balance = 0;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited " << amount << " to savings account. New balance: " << balance << endl;
    }
    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew " << amount << " from savings account. New balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in savings account." << endl;
        }
    }
};

class currentAccount : public Account
{
private:
    double balance;

public:
    currentAccount()
    {
        balance = 0;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited " << amount << " to current account. New balance: " << balance << endl;
    }
    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew " << amount << " from current account. New balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in current account." << endl;
        }
    }
};

class fixedTermAccount : public Account
{
private:
    double balance;

public:
    fixedTermAccount()
    {
        balance = 0;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited " << amount << " to fixed Term account. New balance: " << balance << endl;
    }
    void withdraw(double amount)
    {
        throw logic_error("Withdrawals are not allowed from fixed term account before maturity.");
    }
};

class BankClient
{
private:
    vector<Account *> accounts;

public:
    BankClient(vector<Account *> accounts)
    {
        this->accounts = accounts;
    }
    void processTranactions()
    {
        for (Account *acc : accounts)
        {
            acc->deposit(1000); // all accs allow deposit

            // assuming all accs support withdrawl (LSP Violation)
            try
            {
                acc->withdraw(500);
            }
            catch (const logic_error &e)
            {
                cout << "Exception: " << e.what() << '\n';
            }
        }
    }
};

int main()
{
    vector<Account *> accounts;
    accounts.push_back(new savingsAccount());
    accounts.push_back(new currentAccount());
    accounts.push_back(new fixedTermAccount());

    BankClient *client = new BankClient(accounts);
    client->processTranactions(); // throws exception for fixed term acc.

    return 0;
}
