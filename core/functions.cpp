#include "functions.hpp"

namespace Branches::core
{
    std::map<std::string,std::function<data_t(data_t)>> standard_functions
    {
        {"sin",functions::sin},
        {"sinh",functions::sinh},
        {"cos",functions::cos},
        {"cosh",functions::cosh},
        {"tan",functions::tan},
        {"tanh",functions::tanh},
        {"exp",functions::exp},
        {"ln",functions::ln},
        {"log10",functions::log10},
        {"log2",functions::log2},
        {"abs",functions::abs},

        {"sgn",functions::sgn},
        {"sinc",functions::sinc},
        {"u",functions::u},
        {"rect",functions::rect},
        {"tri",functions::tri},
    };
}

namespace Branches::core::functions
{
    data_t sin(data_t x){return std::sin(x);}
    data_t sinh(data_t x){return std::sinh(x);}
    data_t cos(data_t x){return std::cos(x);}
    data_t cosh(data_t x){return std::cosh(x);}
    data_t tan(data_t x){return std::tan(x);}
    data_t tanh(data_t x){return std::tanh(x);}
    data_t exp(data_t x){return std::exp(x);}
    data_t ln(data_t x){return std::log(x);}
    data_t log10(data_t x){return std::log10(x);}
    data_t log2(data_t x){return std::log2(x);}
    data_t abs(data_t x){return std::abs(x);}

    data_t sgn(data_t x)
    {
        if(x > 0) return 1;
        if(x < 0) return -1;
        else return 0;
    }
    data_t sinc(data_t x)
    {
        if(x == 0) return 1;
        else return sin(PI*x)/(PI*x);
    }
    data_t u(data_t x)
    {
        if(x >= 0) return 1;
        else return 0;
    }
    data_t rect(data_t x)
    {
        if(x > -0.5 && x < 0.5) return 1;
        else return 0;
    }
    data_t tri(data_t x){return (1-abs(x))*rect(x/2);}
}