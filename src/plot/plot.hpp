#pragma once
#include "../parser/parser.hpp"
#include "../integration/integration.hpp"

namespace Branches::plot
{
    void plot(std::vector<parser::Parser>& functions, core::variables_t user_vars, bool complex_out = false);
    void plot_complex(std::vector<parser::Parser>& functions, core::variables_t user_vars, bool complex_out = false);
    void plot_ft(parser::Parser& p, core::variables_t user_vars);
    void plot_ift(parser::Parser& p, core::variables_t user_vars);
}