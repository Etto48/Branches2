#include "plot.hpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
namespace Branches::plot
{
    void plot(std::vector<parser::Parser>& functions, core::variables_t user_vars)
    {
        core::data_t to = user_vars.find("x_max")->second;
        core::data_t from = user_vars.find("x_min")->second;
        core::data_t samples = user_vars.find("samples")->second;
        core::data_t max = user_vars.find("y_max")->second;
        core::data_t min = user_vars.find("y_min")->second;
        core::data_t range_size = to - from;
        core::data_t step = range_size/samples;

        std::vector<core::data_t> x;
        unsigned usamples = (unsigned)std::abs(int(samples));
        
        x.reserve(usamples);
        for (unsigned i = 0; i < usamples; i++)
            x.push_back(i*step+from);

        plt::axvline(0,{{"color","dimgray"}});
        plt::axhline(0,{{"color","dimgray"}});
        plt::grid();
        plt::tight_layout();
        for(auto& f : functions)
        {
            std::vector<core::data_t> y;
            y.reserve(usamples);
            for(auto& px : x)
            {
                std::map<std::string,core::data_t> vars = {{"x",px}};
                vars.insert(user_vars.begin(),user_vars.end());
                core::data_t new_val = f(vars);
                if(new_val >= min && new_val <= max)
                    y.push_back(new_val);
                else 
                    y.push_back(nan(" "));
            }
            plt::plot(x,y);           
        }
        plt::show();
    }
}