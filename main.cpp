#include "main.hpp"

namespace plt = matplotlibcpp;

int main()
{
    
    while(true)
    {
        std::string in_str;
        std::cout << "> ";
        std::cin >> in_str;
        if(in_str == "exit")
            break;
        Branches::parser::Parser p(in_str);
        std::vector<Branches::core::data_t> x,y;
        x.reserve(2000);
        y.reserve(2000);
        for(int i = -1000; i < 1000; i++)
        {
            Branches::core::data_t x_val = double(i)/200.0;
            x.push_back(x_val);
            y.push_back(p({{"x",x_val}}));
        }
        std::cout << "Plotting..." << std::endl;
        plt::plot(x,y);
        plt::show();
    }
    return 0;
}