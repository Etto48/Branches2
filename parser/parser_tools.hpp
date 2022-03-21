#pragma once
#include <string>
#include <tuple>
#include "../exceptions/exceptions.hpp"
#include "../core/core.hpp"

namespace Branches::parser
{
    bool check_braces(const std::string& str);
    std::string remove_wrapping_braces(std::string str);
    bool is_constant(const std::string& str);
    
    bool is_variable(const std::string& str);
    bool is_operator(const std::string& str);
    bool is_prefix(const std::string& str);
    bool is_function(const std::string& str);
    core::data_t get_constant(const std::string& str);
    std::pair<core::OperatorType,std::pair<std::string,std::string>> split_operator(const std::string& str);
    std::pair<bool,std::string> split_prefix(const std::string& str);
    std::pair<std::string,std::string> split_function(const std::string& str);
    void parse(core::Node*& parent, std::string child_content);
}