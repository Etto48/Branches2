#include "functions.hpp"

namespace Branches::core
{
    std::map<std::string,std::function<data_t(data_t)>> standard_functions
    {
        {"re",functions::re},
        {"im",functions::im},

        {"sin",functions::sin},
        {"csc",functions::csc},
        {"sinh",functions::sinh},
        {"cos",functions::cos},
        {"sec",functions::sec},
        {"cosh",functions::cosh},
        {"tan",functions::tan},
        {"cot",functions::cot},
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
        {"flor",functions::floor},

        {"rectw",functions::rectw},
        {"triw",functions::triw},
    };
}

namespace Branches::core::functions
{
    data_t re(data_t x){return x.real();}
    data_t im(data_t x){return x.imag();}
    
    data_t sin(data_t x){return std::sin(x);}
    data_t csc(data_t x){return 1./std::sin(x);}
    data_t sinh(data_t x){return std::sinh(x);}
    data_t cos(data_t x){return std::cos(x);}
    data_t sec(data_t x){return 1./std::cos(x);}
    data_t cosh(data_t x){return std::cosh(x);}
    data_t tan(data_t x){return std::tan(x);}
    data_t cot(data_t x){return 1./std::tan(x);}
    data_t tanh(data_t x){return std::tanh(x);}
    data_t exp(data_t x){return std::exp(x);}
    data_t ln(data_t x){return std::log(x);}
    data_t log10(data_t x){return std::log10(x);}
    data_t log2(data_t x){return std::log(x)/std::log(2.0);}
    data_t abs(data_t x){return std::abs(x);}

    data_t sgn(data_t x)
    {
        if(x.real() > 0) return 1;
        if(x.real() < 0) return -1;
        else return 0;
    }
    data_t sinc(data_t x)
    {
        if(x == 0.0) return 1;
        else return sin(PI*x)/(PI*x);
    }
    data_t u(data_t x)
    {
        if(x.real() >= 0) return 1;
        else return 0;
    }
    data_t rect(data_t x)
    {
        if(std::abs(x) < 0.5) return 1;
        else return 0;
    }
    data_t tri(data_t x){return (1.0-std::abs(x))*rect(x/2.0);}
    data_t floor(data_t x)
    {
        return std::floor(x.real())+data_t{0,1}*std::floor(x.imag());
    }

    data_t rectw(data_t x)
    {
        return sgn(std::sin(2.0*PI*x));
    }
    data_t triw(data_t x)
    {
        return 4*std::abs((x-floor(x+0.5)))-1;
    }
}