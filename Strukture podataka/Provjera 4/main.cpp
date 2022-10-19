#include <iostream>
#include <queue>
#include <stack>
#include <vector>

/* Program napisan ispod predstavlja upravljanje bankovnim racunom.
 * Korisnik ima mogucnost da doda novu transakciju na racun koju je potrebno
 * ubaciti u odredjenu strukturu.
 * Transakcija se aplicira na stanje racuna tek kada korisnik zeli da aplicira
 * transakciju.
 * Korisnik moze da pregleda koja je transakcija spremna za apliciranje te da
 * ispise koje je trenutno stanje racuna.
 * Takodjer, korisnik moze odbaciti transakciju koja je spremna za apliciranje.
 *
 * Zadatak 1
 * Modificirati program na nacin da se transakcija, ako je nije moguce izvrsiti
 * (nema dovoljno stanja na racunu), prebaci na kraj reda transakcija. Takodjer, program treba da ispise odgovarajucu poruku.
 *
 * Zadatak 2
 * Implementirati novu opciju 7, koja treba da izvrsi sve transakcije redom,
 * dokle god je to moguce odraditi.
 *
 * Zadatak 3
 * Implementirati novu opciju 8, koja treba da izvrsi sve pozitivne transakcije,
 * a sve negativne transakcije da ostavi na kraju reda.
 */

int getTransaction()
{
    std::cout << "Enter transaction value: ";
    int num;
    std::cin >> num;
    return num;
}

int main(int argc, char *argv[])
{
    int balance = 0; // Pocetno stanje racuna

    std::queue<int> transactions;

    while (1)
    {
        std::cout << std::endl;
        std::cout << "**********************************" << std::endl;
        std::cout << "Actions: " << std::endl;
        std::cout << "\t1. New transaction" << std::endl;
        std::cout << "\t2. Apply transaction" << std::endl;
        std::cout << "\t3. Pending transaction" << std::endl;
        std::cout << "\t4. Discard pending transaction" << std::endl;
        std::cout << "\t5. Ballance" << std::endl;
        std::cout << "\t6. Exit" << std::endl;
        std::cout << "\t7. Apply all transactions" << std::endl;
        std::cout << "Your choice? ";
        int choice;
        std::cin >> choice;
        if (choice == 1)
        {
            int transaction = getTransaction();
            transactions.push(transaction);
        }
        else if (choice == 2)
        {
            if (!transactions.empty())
            {
                if ((balance + transactions.front()) < 0)
                {
                    std::cout << "Insufficient funds" << std::endl;
                    int pushToLast = transactions.front();
                    transactions.pop();
                    transactions.push(pushToLast);
                }
                else
                {
                    balance += transactions.front();
                    transactions.pop();
                }
            }
        }
            else if (choice == 3)
            {
                if (!transactions.empty())
                {
                    std::cout << transactions.front();
                }
            }
            else if (choice == 4)
            {
                if (!transactions.empty())
                {
                    transactions.pop();
                }
            }
            else if (choice == 5)
            {
                std::cout << "Balance is: " << balance << std::endl;
            }
            else if (choice == 6)
            {
                break;
            }
            else if (choice == 7)
            {
                for (int i = 0; i <= transactions.size(); ++i)
                {
                    if (balance + transactions.front() > 0)
                    {
                        balance += transactions.front();
                        transactions.pop();
                    }
                    else if (balance + transactions.front() < 0)
                    {
                        std::cout << "Insufficient funds" << std::endl;
                        int pushToLast = transactions.front();
                        transactions.pop();
                        transactions.push(pushToLast);
                    }
                }
            }
            else
            {
                std::cout << "Incorrect input!" << std::endl;
            }
        }
        std::cout << "Goodbye" << std::endl;
        std::cout << "**********************************" << std::endl;
        return 0;
    }
