#include "core.hpp"

namespace Branches::core
{
    variables_t constants{
        {"pi", PI},
        {"e", E},
        {"i",{0,1}},
        {"j",{0,1}},
    };

    ConstantNode::ConstantNode(data_t value) : value(value) {}
    data_t ConstantNode::operator()([[maybe_unused]] variables_t variables)
    {
        return value;
    }
    std::string ConstantNode::text()
    {
        return value.real()==0 ? std::to_string(value.imag())+"i" : std::to_string(value.real());
    }
    std::string ConstantNode::derivative(const std::string &var)
    {
        return "0";
    }

    VariableNode::VariableNode(std::string name) : name(name) {}
    data_t VariableNode::operator()(variables_t variables)
    {
        auto i = variables.find(name);
        if (i == variables.end())
            throw exceptions::UnknownVariable{name};
        else
            return i->second;
    }
    std::string VariableNode::text()
    {
        return name;
    }
    std::string VariableNode::derivative(const std::string &var)
    {
        return var == name ? "1" : "0";
    }

    OperatorNode::OperatorNode(OperatorType op, Node *left, Node *right) : op(op), children(left, right) {}
    data_t OperatorNode::operator()(variables_t variables)
    {
        auto a = children.first->operator()(variables);
        auto b = children.second->operator()(variables);
        switch (op)
        {
        case OperatorType::sum:
            return a + b;
            break;
        case OperatorType::subtraction:
            return a - b;
            break;
        case OperatorType::product:
            return a * b;
            break;
        case OperatorType::division:
            // TODO: calculate the limit if both are 0
            if( a == b )
                return 1.0;
            return a / b;
            break;
        case OperatorType::power:
            return std::pow(a, b);
            break;
        default:
            return 0;
        }
    }
    std::string OperatorNode::text()
    {
        auto a = children.first->text();
        auto b = children.second->text();
        switch (op)
        {
        case OperatorType::sum:
            return "(" + a + ")+(" + b + ")";
            break;
        case OperatorType::subtraction:
            return "(" + a + ")-(" + b + ")";
            break;
        case OperatorType::product:
            return "(" + a + ")*(" + b + ")";
            break;
        case OperatorType::division:
            // TODO: calculate the limit if both are 0
            return "(" + a + ")/(" + b + ")";
            break;
        case OperatorType::power:
            return "(" + a + ")^(" + b + ")";
            break;
        default:
            return "";
        }
    }
    std::string OperatorNode::derivative(const std::string &var)
    {
        auto da = children.first->derivative(var);
        auto db = children.second->derivative(var);
        auto a = children.first->text();
        auto b = children.second->text();
        switch (op)
        {
        case OperatorType::sum:
            if(da=="0")
                return db;
            else if(db == "0")
                return da;
            else
                return "(" + da + ")+(" + db + ")";
            break;
        case OperatorType::subtraction:
            if(da=="0")
                return "-("+db+")";
            else if(db == "0")
                return da;
            else
                return "(" + da + ")-(" + db + ")";
            break;
        case OperatorType::product:
            {
                std::string fh, sh;
                if(da == "0" || b == "0")
                    fh = "0";
                else if(da == "1" || b == "1")
                    fh = "1";
                else 
                    fh = "(" + da + ")*(" + b + ")";

                if(a == "0" || db == "0")
                    sh = "0";
                else if(a == "1" || db == "1")
                    sh = "1";
                else
                    sh = "(" + a + ")*(" + db + ")";

                if(fh == "0")
                    return sh;
                else if(sh == "0")
                    return fh;
                else
                    return fh+"+"+sh;
            }
            break;
        case OperatorType::division:
            return "((" + da + ")*(" + b + ")-(" + a + ")*(" + db + "))/(" + b + ")^2";
            break;
        case OperatorType::power:
            return "(" + a + ")^((" + b + ") - 1)*(("+b+")*("+da+")+("+a+")*ln("+a+")*("+db+"))";
            break;
        default:
            return "";
        }
    }

    PrefixNode::PrefixNode(bool negative, Node *child) : negative(negative), child(child) {}
    data_t PrefixNode::operator()(variables_t variables)
    {
        if (negative)
            return -child->operator()(variables);
        else
            return +child->operator()(variables);
    }
    std::string PrefixNode::text()
    {
        auto a = child->text();
        return negative?"-("+a+")":""+a+"";
    }
    std::string PrefixNode::derivative(const std::string& var)
    {
        auto a = child->derivative(var);
        return negative?"-("+a+")":""+a+"";
    }

    FunctionNode::FunctionNode(std::string name, Node *child) : name(name), child(child) {}
    data_t FunctionNode::operator()(variables_t variables)
    {
        auto a = child->operator()(variables);
        auto i = standard_functions.find(name);
        if (i == standard_functions.end())
            throw exceptions::UnknowFunction{name};
        else
            return i->second(a);
    }
    std::string FunctionNode::text()
    {
        auto a = child->text();
        return name + "("+a+")";
    }
    std::string FunctionNode::derivative(const std::string& var)
    {
        auto a = child->text();
        auto da = child->derivative(var);
        
        std::string fh;
        if(name == "sin")
        {
            fh = "cos("+a+")";
        }
        else if(name == "csc")
        {
            return "";
        }
        else if(name == "sinh")
        {
            return "";
        }
        else if(name == "cos")
        {
            fh = "-sin("+a+")";
        }
        else if(name == "sec")
        {
            return "";
        }
        else if(name == "cosh")
        {
            return "";
        }
        else if(name == "tan")
        {
            return "(" + da + ")/tan(" + a + ")^2";
        }
        else if(name == "cot")
        {
            return "";
        }
        else if(name == "tanh")
        {
            return "";
        }
        else if(name == "exp")
        {
            fh = "exp(" + a + ")";
        }
        else if(name == "ln")
        {
            return "(" + da + ")/(" + a + ")";
        }
        else if(name == "log10")
        {
            return "(" + da + ")/((" + a + ")*ln(10))";
        }
        else if(name == "log2")
        {
            return "(" + da + ")/((" + a + ")*ln(2))";
        }
        else if(name == "abs")
        {
            fh = "sng("+a+")";
        }
        else if(name == "sgn")
        {
            return "";
        }
        else if(name == "sinc")
        {
            return "";
        }
        else if(name == "u")
        {
            return "";
        }
        else if(name == "rect")
        {
            return "";
        }
        else if(name == "tri")
        {
            return "";
        }
        else
        {
            throw exceptions::UnknowFunction(name);
        }
        if(da == "0")
            return "0";
        else if(da == "1")
            return fh;
        else 
            return fh+"*("+da+")";
    }
}