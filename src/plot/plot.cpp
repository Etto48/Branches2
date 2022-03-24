#include "plot.hpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
namespace Branches::plot
{
    void plot(std::vector<parser::Parser>& functions, unsigned samples, core::data_t from, core::data_t to)
    {
        core::data_t range_size = to - from;
        core::data_t step = range_size/samples;

        std::vector<core::data_t> x;
        x.reserve(samples);
        for (unsigned i = 0; i < samples; i++)
            x.push_back(i*step+from);

        plt::axvline(0,{{"color","dimgray"}});
        plt::axhline(0,{{"color","dimgray"}});
        plt::grid();
        plt::tight_layout();
        for(auto& f : functions)
        {
            std::vector<core::data_t> y;
            y.reserve(samples);
            for(auto& px : x)
            {
                y.push_back(f({{"x",px}}));
            }
            plt::plot(x,y);           
        }
        plt::show();
    }
}