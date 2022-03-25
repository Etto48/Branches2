#pragma once
#include "../parser/parser.hpp"

namespace Branches::plot
{
    void plot(std::vector<parser::Parser>& functions, core::variables_t user_vars, core::data_t samples = 2000, core::data_t from = -5, core::data_t to = 5);
}