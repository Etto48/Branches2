#include "main.hpp"

int main()
{
    
    while(true)
    {
        std::string in_str;
        std::cin >> in_str;
        if(in_str == "exit")
            break;
        Branches::parser::Parser p(in_str);
        std::cout << in_str << '=' << p({}) << std::endl;
    }
    return 0;
}