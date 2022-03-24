#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "../parser/parser.hpp"
#include "../plot/plot.hpp"

namespace Branches::cli
{
    std::vector<std::string> split_command(const std::string& cmd);
    void start_cli();
}
