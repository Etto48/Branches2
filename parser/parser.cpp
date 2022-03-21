#include "parser.hpp"

namespace Branches::parser
{
    Parser::Parser(const std::string& _source):source(_source)
    {
        core::Node* _root;
        parse(_root,source);
        root = core::Node::Pointer{_root};
    }

    core::data_t Parser::operator()(core::variables_t variables)
    {
        auto sub_list = variables;
        sub_list.insert(core::constants.begin(),core::constants.end());
        return root->operator()(sub_list);
    }
}