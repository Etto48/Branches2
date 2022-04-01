#pragma once

#include "../parser/parser.hpp"
#include <complex>
#include <string>

namespace Branches::integration
{
    core::data_t integrate(double from, double to, parser::Parser& p, const std::string& var, core::variables_t user_vars);
    std::vector<core::data_t> sft(parser::Parser& p, core::variables_t user_vars);
    std::vector<core::data_t> isft(parser::Parser& p, core::variables_t user_vars);
}