#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <functional>
#include <math.h>
#include "../exceptions/exceptions.hpp"
#include "types.hpp"

namespace Branches::core
{
    extern std::map<std::string,std::function<data_t(data_t)>> standard_functions;
    extern variables_t constants;

    enum class NodeType
    {
        ConstantNode, VariableNode, OperatorNode, PrefixNode, FunctionNode
    };

    class Node
    {
    protected:
    public:
        typedef std::unique_ptr<Node> Pointer;
        virtual NodeType type() = 0;
        virtual data_t operator()(variables_t variables) = 0;
    };

    class ConstantNode: public Node
    {
    protected:
        data_t value;
    public:
        ConstantNode(data_t value);
        NodeType type(){return NodeType::ConstantNode;}
        virtual data_t operator()(variables_t variables);
    };

    class VariableNode: public Node
    {
    protected:
        std::string name;
    public:
        VariableNode(std::string name);
        NodeType type(){return NodeType::VariableNode;}
        virtual data_t operator()(variables_t variables);
    };

    enum class OperatorType
    {
        sum, subtraction, product, division, power
    };

    class OperatorNode: public Node
    {
    protected:
        OperatorType op;
        std::pair<Node::Pointer,Node::Pointer> children;
    public:
        OperatorNode(OperatorType op, Node* left, Node* right);
        NodeType type(){return NodeType::OperatorNode;}
        virtual data_t operator()(variables_t variables);
    };

    class PrefixNode: public Node
    {
    protected:
        bool negative;
        Node::Pointer child;
    public:
        PrefixNode(bool negative, Node* child);
        NodeType type(){return NodeType::PrefixNode;}
        virtual data_t operator()(variables_t variables);
    };

    class FunctionNode: public Node
    {
    protected:
        std::string name;
        Node::Pointer child;
    public:
        FunctionNode(std::string name, Node* child);
        NodeType type(){return NodeType::FunctionNode;}
        virtual data_t operator()(variables_t variables);
    };
}