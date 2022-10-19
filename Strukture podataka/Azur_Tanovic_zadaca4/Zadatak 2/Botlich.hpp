#include <stack>
#include <string>
#include <exception>
#include <iostream>

class Botlich
{

private:
    std::stack<int> bracketsPriority;

public:
    void check(std::string in)
    {
        auto priority = [&](const int &number)
        {
            if (!(bracketsPriority.empty()))
                if (number > bracketsPriority.top())
                    throw std::string("FAIL");
            bracketsPriority.push(number);
        };

        auto closeBrackets = [&](const int &number)
        {
            if (bracketsPriority.top() != number)
                throw std::string("FAIL");
            bracketsPriority.pop();
        };

        for (int i = 0; i < in.size(); ++i)
        {
            switch (in[i])
            {
            case '{':
                priority(4);
                break;
            case '[':
                priority(3);
                break;
            case '(':
                priority(2);
                break;
            case '<':
                priority(1);
                break;
            case '>':
                closeBrackets(1);
                break;
            case ')':
                closeBrackets(2);
                break;
            case ']':
                closeBrackets(3);
                break;
            case '}':
                closeBrackets(4);
                break;

            default:
                throw std::string("FAIL");
                break;
            }
        }

        std::cout << "PASS" << std::endl;
    }
};