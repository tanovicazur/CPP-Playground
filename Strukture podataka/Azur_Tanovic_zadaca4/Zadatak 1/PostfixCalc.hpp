#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

class PostfixCalc{
    private:
        std::stack<double> operands;
    public:
        double calculate(std::string in){
            double result;
            std::stringstream input(in);
            std::string temp;
            double firstOp,secOp;
                
            while(input>>temp){
                if(temp == "+"){
                    secOp = operands.top();
                    operands.pop();
                    firstOp = operands.top();
                    operands.pop();
                    operands.push(firstOp + secOp);
                }
                else if(temp == "-"){
                    secOp = operands.top();
                    operands.pop();
                    firstOp = operands.top();
                    operands.pop();
                    operands.push(firstOp - secOp);
                }
                else if(temp == "*"){
                    secOp = operands.top();
                    operands.pop();
                    firstOp = operands.top();
                    operands.pop();
                    operands.push(firstOp * secOp);
                }
                else if(temp == "/"){
                    secOp = operands.top();
                    operands.pop();
                    firstOp = operands.top();
                    operands.pop();
                    operands.push(firstOp / secOp);
                }
                else{
                    operands.push(stod(temp));
                }        
            }

            result = operands.top();
            operands.pop();
            return result;
        }
};