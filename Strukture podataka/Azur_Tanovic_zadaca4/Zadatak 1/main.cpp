#include "PostfixCalc.hpp"

int main(){
    PostfixCalc p;
    std::cout<<p.calculate("3 4 * 2 5 * +");
}
