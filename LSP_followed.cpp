#include <iostream>
#include <vector>
using namespace std;

class NonWithdrawableAccount
{
public:
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount : public NonWithdrawableAccount
{
public:
    virtual void withdraw(double amount) = 0;
};

class SavingsAccount : public WithdrawableAccount
{
private:
    double balance;

public:
    SavingsAccount()
    {
        balance = 0;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited " << amount << " to Savings account. New balance: " << balance << endl;
    }
    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew " << amount << " from Savings account. New balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Savings account." << endl;
        }
    }
};

class CurrentAccount : public WithdrawableAccount
{
private:
    double balance;

public:
    CurrentAccount()
    {
        balance = 0;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited " << amount << " to Current account. New balance: " << balance << endl;
    }
    void withdraw(double amount)
    {
        if (balance >= amount)
        {
            balance -= amount;
            cout << "Withdrew " << amount << " from Current account. New balance: " << balance << endl;
        }
        else
        {
            cout << "Insufficient funds in Current account." << endl;
        }
    }
};

class FixedTermAccount : public NonWithdrawableAccount
{
private:
    double balance;

public:
    FixedTermAccount()
    {
        balance = 0;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Deposited " << amount << " to Fixed Term account. New balance: " << balance << endl;
    }
};

class BankClient
{
private:
    vector<NonWithdrawableAccount *> nonWithdrawableAccounts;
    vector<WithdrawableAccount *> withdrawableAccounts;

public:
    BankClient(vector<NonWithdrawableAccount *> nonWithdrawableAccounts, vector<WithdrawableAccount *> withdrawableAccounts)
    {
        this->nonWithdrawableAccounts = nonWithdrawableAccounts;
        this->withdrawableAccounts = withdrawableAccounts;
    }
    void processTransactions()
    {
        for (NonWithdrawableAccount *acc : nonWithdrawableAccounts)
        {
            acc->deposit(1000); // all non-withdrawable accounts allow deposit only
        }

        for (WithdrawableAccount *acc : withdrawableAccounts)
        {
            acc->deposit(1000); // all withdrawable accounts allow deposit
            acc->withdraw(500); // all withdrawable accounts allow withdrawal
        }
    }
};

int main()
{
    vector<WithdrawableAccount *> withdrawableAccounts;
    withdrawableAccounts.push_back(new SavingsAccount());
    withdrawableAccounts.push_back(new CurrentAccount());

    vector<NonWithdrawableAccount *> nonWithdrawableAccounts;
    nonWithdrawableAccounts.push_back(new FixedTermAccount());

    BankClient *client = new BankClient(nonWithdrawableAccounts, withdrawableAccounts);
    client->processTransactions();

    return 0;
}
