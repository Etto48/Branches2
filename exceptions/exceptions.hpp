#pragma once
#include <exception>
#include <string>

namespace Branches::exceptions
{
    struct Error: public std::exception
    {
        std::string error;
        Error(const std::string& error):error(error){}
        const char* what() const throw()
        {
            return error.c_str();
        }
    };

    struct MathError: public Error
    {
        MathError():Error("MathError"){}
    };

    struct UnknownVariable: public Error
    {
        UnknownVariable():Error("UnknownVariable"){}
        UnknownVariable(const std::string& var):Error("UnknownVariable: "+var){}
    };

    struct UnknowFunction: public Error
    {
        UnknowFunction():Error("UnknownFunction"){}
        UnknowFunction(const std::string& fun):Error("UnknownFunction: "+fun){}
    };

    struct UnbalancedBraces: public Error
    {
        UnbalancedBraces():Error("UnbalancedBraces"){}
    };

    struct EmptyBraces: public Error
    {
        EmptyBraces():Error("EmptyBraces"){}
    };

    struct OperatorMisplaced: public Error
    {
        OperatorMisplaced():Error("OperatorMisplaced"){}
    };

    struct ParsingError: public Error
    {
        ParsingError():Error("ParsingError"){}
    };
}