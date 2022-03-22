#include "main.hpp"

namespace plt = matplotlibcpp;

int main()
{
    std::vector<std::vector<Branches::core::data_t>> ys;
    std::vector<Branches::core::data_t> x;
    x.reserve(2000);
    for(int i = -1000; i < 1000; i++)
    {
        Branches::core::data_t x_val = double(i)/200.0;
        x.push_back(x_val);
    }
    while(true)
    {
        std::string in_str;
        std::cout << "> ";
        std::cin >> in_str;
        if(in_str == "exit")
            break;
        else if(in_str == "plot")
        {
            std::cout << "Plotting..." << std::endl;
            for(auto& y : ys)
                plt::plot(x,y);
            
            plt::show();
        }
        else if(in_str == "clear")
            ys.clear();
        else
        {
            Branches::parser::Parser p(in_str);
            std::vector<Branches::core::data_t> y;
            y.reserve(2000);
            for(auto& x_val : x)
                y.push_back(p({{"x",x_val}}));
            ys.push_back(y);
        }
    }
    return 0;
}