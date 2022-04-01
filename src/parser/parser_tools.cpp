#include "parser_tools.hpp"

namespace Branches::parser
{
    bool check_braces(const std::string &str)
    {
        int d = 0;
        for (auto &c : str)
        {
            switch (c)
            {
            case '(':
                d++;
                break;
            case ')':
                d--;
                break;
            default:
                break;
            }
            if (d < 0)
                return false;
        }
        if (d != 0)
            return false;
        else 
            return true;
    }
    std::string remove_wrapping_braces(std::string str)
    {
        while (str.front() == '(' && str.back() == ')')
        {
            if (str.length() == 2)
                throw exceptions::EmptyBraces{};
            int d = 0;
            int conj = -1;
            for (int i = 0; i < (int)str.length(); i++)
            {
                auto &c = str[i];
                if (c == '(')
                    d++;
                else if (c == ')')
                {
                    d--;
                    if (d == 0)
                    {
                        conj = i;
                        break;
                    }
                }
            }
            if (conj == (int)str.length() - 1)
            {
                str.erase(0, 1);
                str.erase(str.length() - 1, 1);
            }
            else break;
        }
        return str;
    }
    bool is_constant(const std::string &str)
    {
        bool dot_used = false;
        for (unsigned i = 0; i < str.size(); i++)
        {
            auto& c = str[i];
            if (c < '0' || c > '9')
            {
                if (c == '.' && !dot_used)
                {
                    dot_used = true;
                }
                else if(!((c == 'i' || c == 'j')&&(i==str.size()-1)))
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool is_variable(const std::string &str)
    {
        if (str[0] < '0' || str[0] > '9')
        {
            for (int i = 1; i < (int)str.length(); i++)
            {
                auto &c = str[i];
                if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') && (c < '0' || c > '9') && (c != '_'))
                {
                    return false;
                }
            }
            return true;
        }
        else
            return false;
    }
    bool is_operator(const std::string &str)
    {
        int d = 0;
        for (int i = 0; i < (int)str.length(); i++)
        {
            auto& c = str[i];
            if (c == '(')
            {
                d++;
            }
            else if (c == ')')
            {
                d--;
            }
            else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
            {
                if (d == 0 && i != 0)
                {
                    return true;
                }
            }
        }
        return false;
    }
    bool is_prefix(const std::string &str)
    {
        if (str[0] == '+' || str[0] == '-')
        {
            int d = 0;
            for (int i = 0; i < (int)str.length(); i++)
            {
                auto& c = str[i];
                if (c == '(')
                {
                    d++;
                }
                else if (c == ')')
                {
                    d--;
                }
                else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
                {
                    if (d == 0 && i != 0)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
        else
            return false;
    }
    bool is_function(const std::string &str)
    {
        int d = 0;
        int conj = -1;
        bool name = true;
        if (str.front() != '(' && str.back() == ')')
        {
            for (int i = 0; i < (int)str.length(); i++)
            {
                auto &c = str[i];
                if (c == '(')
                {
                    name = false;
                    d++;
                }
                else if (c == ')')
                {
                    d--;
                    if (d == 0)
                    {
                        conj = i;
                        break;
                    }
                }
                else if(name)
                {
                    if((c < 'A' || c > 'Z')&&(c < 'a' || c > 'z') && (c != '_'))
                    {
                        if(i == 0)
                            return false;
                        else if(c < '0' || c > '9')
                            return false;
                    }
                }
            }
            if (conj == (int)str.length() - 1)
            {
                return true;
            }
        }
        return false;
    }
    core::data_t get_constant(const std::string &str)
    {
        bool imag = false;
        std::string new_str = str;
        if(new_str.back()=='i' || new_str.back()=='j')
        {
            imag = true;
            new_str.pop_back();
        }
        return std::stod(new_str) * (imag? core::data_t{0,1} : core::data_t{1,0});
    }
    std::pair<core::OperatorType, std::pair<std::string, std::string>> split_operator(const std::string &str)
    {
        int d = 0;
        // operator priority: ^, * /, + -
        // must split on the lower priority
        int priority_level = 0; // 0 = ^, 1 = * /, 2 = + -
        int operator_index = -1;
        for (int i = 0; i < (int)str.length(); i++)
        {
            auto &c = str[i];
            if (c == '(')
            {
                d++;
            }
            else if (c == ')')
            {
                d--;
            }
            else if (c == '+' || c == '-' || c == '/' || c == '*' || c == '^')
            {
                if (d == 0 && i > 0 && str[i - 1] != '+' && str[i - 1] != '-' && str[i - 1] != '/' && str[i - 1] != '*' && str[i - 1] != '^')
                {
                    int tmp_priority = 0;
                    switch (c)
                    {
                    case '+':
                    case '-':
                        tmp_priority = 2;
                        break;
                    case '*':
                    case '/':
                        tmp_priority = 1;
                        break;
                    case '^':
                        tmp_priority = 0;
                        break;
                    }
                    if (tmp_priority >= priority_level)
                    { // we save the position
                        operator_index = i;
                        priority_level = tmp_priority;
                    }
                }
            }
        }
        if ((int)str.length() < operator_index + 2)
            throw exceptions::OperatorMisplaced{};
        std::string first = str.substr(0, operator_index);
        std::string second = str.substr(operator_index + 1);
        core::OperatorType op;
        switch (str[operator_index])
        {
        case '+':
            op = core::OperatorType::sum;
            break;
        case '-':
            op = core::OperatorType::subtraction;
            break;
        case '*':
            op = core::OperatorType::product;
            break;
        case '/':
            op = core::OperatorType::division;
            break;
        case '^':
            op = core::OperatorType::power;
            break;
        }
        return {op, {first, second}};
    }
    std::pair<bool, std::string> split_prefix(const std::string &str)
    {
        bool negative = false;
        if(str[0]=='-')
            negative = true;
        return {negative,str.substr(1)};
    }
    std::pair<std::string, std::string> split_function(const std::string &str)
    {
        int i = 0;
        for(i = 0; i < (int)str.length() && str[i] != '('; i++);
        std::string name = str.substr(0,i);
        std::string content = str.substr(i);
        return {name,content};
    }
    void parse(core::Node *&parent, std::string child_content)
    {
        if (!check_braces(child_content))
            throw exceptions::UnbalancedBraces{};
        else
        {
            child_content = remove_wrapping_braces(child_content);
            bool check_function = is_function(child_content);
            bool check_prefix = is_prefix(child_content);
            bool check_operator = is_operator(child_content);
            bool check_variable = is_variable(child_content);
            bool check_constant = is_constant(child_content);

            core::NodeType type;

            if(check_function)
                type = core::NodeType::FunctionNode;
            else if(check_operator)
                type = core::NodeType::OperatorNode;//check before if there is an operator because it has more priority
            else if(check_prefix)
                type = core::NodeType::PrefixNode;
            else if(check_variable)
                type = core::NodeType::VariableNode;
            else if(check_constant)
                type = core::NodeType::ConstantNode;
            else
                throw exceptions::ParsingError{};

            switch (type)
            {
            case core::NodeType::FunctionNode:
                {
                    auto data = split_function(child_content);
                    core::Node* child;
                    parse(child,data.second);
                    parent = new core::FunctionNode(data.first,child);
                }
                break;
            case core::NodeType::PrefixNode:
                {
                    auto data = split_prefix(child_content);
                    core::Node* child;
                    parse(child,data.second);
                    parent = new core::PrefixNode(data.first,child);
                }
                break;
            case core::NodeType::OperatorNode:
                {
                    auto data = split_operator(child_content);
                    core::Node* child_first;
                    core::Node* child_second;
                    parse(child_first,data.second.first);
                    parse(child_second,data.second.second);
                    parent = new core::OperatorNode(data.first,child_first,child_second);
                }
                break;
            case core::NodeType::VariableNode:
                {
                    parent = new core::VariableNode(child_content);
                }
                break;
            case core::NodeType::ConstantNode:
                {
                    auto data = get_constant(child_content);
                    parent = new core::ConstantNode(data);
                }
                break;
            }
        }
    }
}