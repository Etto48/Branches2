#include "core.hpp"

namespace Branches::core
{
    variables_t constants
    {
        {"pi",PI},
        {"e",E}
    };

    ConstantNode::ConstantNode(data_t value):value(value){}
    data_t ConstantNode::operator()([[maybe_unused]]variables_t variables)
    {
        return value;
    }

    VariableNode::VariableNode(std::string name):name(name){}
    data_t VariableNode::operator()(variables_t variables)
    {
        auto i = variables.find(name);
        if(i == variables.end())
            throw exceptions::UnknownVariable{name};
        else
            return i->second;
    }

    OperatorNode::OperatorNode(OperatorType op, Node* left, Node* right):op(op),children(left,right){}
    data_t OperatorNode::operator()(variables_t variables)
    {
        auto a = children.first->operator()(variables);
        auto b = children.second->operator()(variables);
        switch (op)
        {
        case OperatorType::sum:
            return a+b;
            break;
        case OperatorType::subtraction:
            return a-b;
            break;
        case OperatorType::product:
            return a*b;
            break;
        case OperatorType::division:
            //TODO: calculate the limit if both are 0
            return a/b;
            break;
        case OperatorType::power:
            return std::pow(a,b);
            break;
        default:
            return 0;
        }
    }

    PrefixNode::PrefixNode(bool negative, Node* child):negative(negative),child(child){}
    data_t PrefixNode::operator()(variables_t variables)
    {
        if(negative)
            return - child->operator()(variables);
        else
            return + child->operator()(variables);
    }

    FunctionNode::FunctionNode(std::string name, Node* child):name(name),child(child){}
    data_t FunctionNode::operator()(variables_t variables)
    {
        auto a = child->operator()(variables);
        auto i = standard_functions.find(name);
        if(i == standard_functions.end())
            throw exceptions::UnknowFunction{name};
        else
            return i->second(a);
    }
}