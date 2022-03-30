#pragma once
#include <map>
#include <string>
#include <functional>
#include <math.h>
#include "types.hpp"

namespace Branches::core
{
    extern std::map<std::string,std::function<data_t(data_t)>> standard_functions;
}

namespace Branches::core::functions
{
    data_t sin(data_t x);
    data_t csc(data_t x);
    data_t sinh(data_t x);
    data_t cos(data_t x);
    data_t sec(data_t x);
    data_t cosh(data_t x);
    data_t tan(data_t x);
    data_t cot(data_t x);
    data_t tanh(data_t x);
    data_t exp(data_t x);
    data_t ln(data_t x);
    data_t log10(data_t x);
    data_t log2(data_t x);
    data_t abs(data_t x);

    data_t sgn(data_t x);
    data_t sinc(data_t x);
    data_t u(data_t x);
    data_t rect(data_t x);
    data_t tri(data_t x);
}