#include "bankAcc.hpp"
#include <stdlib.h>

int main()
{
    BankAcc myacc;
    int input;

    while (true)
    {
        std::cout << "==================================================" << std::endl;
        std::cout << "1.New transaction" << std::endl;
        std::cout << "2.Apply transaction" << std::endl;
        std::cout << "3.Pending transaction" << std::endl;
        std::cout << "4.Discard transaction" << std::endl;
        std::cout << "5.Balance" << std::endl;
        std::cout << "6.Exit" << std::endl;
        std::cout << std::endl;

        std::cout << "Your choice?";
        std::cin >> input;

        switch (input)
        {
        case 1:
            myacc.newTransaction();
            break;
        case 2:
            myacc.applyTransaction();
            break;
        case 3:
            myacc.pendingTransaction();
            break;
        case 4:
            myacc.discardTransaction();
            break;
        case 5:
            myacc.balance_of_acc();
            break;
        case 6:
            std::exit(1);
        }
    }
}
