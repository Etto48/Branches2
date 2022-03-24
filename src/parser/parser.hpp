#pragma once
#include <string>
#include "../core/core.hpp"
#include "../exceptions/exceptions.hpp"
#include "parser_tools.hpp"

namespace Branches::parser
{
    class Parser
    {
    protected:
        std::string source;
        core::Node::Pointer root;
    public:
        Parser(const std::string& _source);
        const std::string& get_source();
        core::data_t operator()(core::variables_t variables);
    };
}