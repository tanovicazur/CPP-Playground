#pragma once

#include <queue>
#include <iostream>

class Transaction
{
public:
    std::string date;
    double value;
};
class BankAcc
{
private:
    std::queue<Transaction> transactions;
    double balance;
public:
    BankAcc() : balance{0} {}
    void newTransaction()
    {
        Transaction tr;
        std::cout << "********************DODAVANJE TRANSAKCIJE*******************************" << std::endl;
        std::cout << "DATUM:";
        std::cin >> tr.date;
        std::cout << "Vrijednost transakcije(dodavanje ili oduzimanje):";
        std::cin >> tr.value;
        std::cout << std::endl;
        transactions.push(tr);
    }

    void applyTransaction()
    {
        std::cout << "************************************" << std::endl;
        if (transactions.empty())
        {
            std::cout << "NEMA VISE TRANSAKCIJA" << std::endl;
            return;
        }
        std::cout << "TRANSAKCIJA JE USPJESNO APLICIRANA" << std::endl;
        std::cout << std::endl;
        balance += transactions.front().value;
        transactions.pop();
    }
    void pendingTransaction() const
    {
        if (transactions.empty())
        {
            std::cout << "NEMA VISE TRANSAKCIJA" << std::endl;
            return;
        }
        std::cout << "***************** TRANSAKCIJA  *****************" << std::endl;
        std::cout << "DATUM:" << transactions.front().date << std::endl;
        std::cout << "VRIJEDNOST:" << transactions.front().value << std::endl;
    }

    void balance_of_acc() const
    {
        std::cout << "**************BALANS*******************" << std::endl;
        std::cout << "BALANS RACUNA:" << balance << std::endl;
    }

    void discardTransaction()
    {
        if (transactions.empty())
        {
            std::cout << "NEMA VISE TRANSAKCIJA!" << std::endl;
            return;
        }
        transactions.pop();
        std::cout << "TRANSAKCIJA USPJESNO OBRISANA!" << std::endl;
        std::cout << std::endl;
    }
};
