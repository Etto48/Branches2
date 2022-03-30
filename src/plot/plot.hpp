#pragma once
#include "../parser/parser.hpp"

namespace Branches::plot
{
    void plot(std::vector<parser::Parser>& functions, core::variables_t user_vars);
}