#include "cli.hpp"

namespace Branches::cli
{
    constexpr core::data_t default_samples = 2000, default_x_min = -5, default_x_max = 5;
    std::map<std::string, Branches::core::data_t> user_vars =
        {
            {"x_min", default_x_min},
            {"x_max", default_x_max},
            {"samples", default_samples},
    };
    std::vector<Branches::parser::Parser> functions;
    std::string prompt()
    {
        return "Functions: " + std::to_string(functions.size()) + ", Vars: " + std::to_string(user_vars.size()) + " > ";
    }

    std::vector<std::string> split_command(const std::string &cmd)
    {
        std::stringstream ss(cmd);
        std::vector<std::string> ret;
        std::string token;
        while (ss >> token)
            ret.push_back(token);
        return ret;
    }

    void start_cli()
    {
        std::cout << "Welcome to Branches" << std::endl;
        std::cout << "Write \"help\" to get a list of commands" << std::endl;
        while (true)
        {
            std::string cmd;
            std::cout << prompt();
            std::getline(std::cin, cmd);
            auto tokens = split_command(cmd);
            if (tokens.size() == 1 && tokens[0] == "exit")
            {
                break;
            }
            else if (tokens.size() == 1 && tokens[0] == "ls")
            {
                for (unsigned i = 0; i < functions.size(); i++)
                    std::cout << i + 1 << ") " << functions[i].get_source() << std::endl;
            }
            else if (tokens.size() > 1 && tokens[0] == "add")
            {
                for (unsigned i = 1; i < tokens.size(); i++)
                    functions.emplace_back(tokens[i]);
            }
            else if (tokens.size() > 1 && tokens[0] == "rm")
            {
                if (tokens.size() == 2 && tokens[1] == "*")
                    functions.clear();
                else
                {
                    int erased = 0;
                    for (unsigned i = 1; i < tokens.size(); i++)
                    {
                        int index = std::atoi(tokens[i].c_str()) - 1 - erased;
                        if (index < 0)
                            continue;
                        if (index < functions.size())
                        {
                            functions.erase(functions.begin() + index);
                            erased++;
                        }
                    }
                }
            }
            else if (tokens.size() > 1 && tokens[0] == "rmv")
            {
                if (tokens.size() == 2 && tokens[1] == "*")
                {
                    user_vars.clear();
                    user_vars = {
                        {"x_min", default_x_min},
                        {"x_max", default_x_max},
                        {"samples", default_samples},
                    };
                }
                else
                {
                    for(unsigned i = 1; i < tokens.size(); i++)
                    {
                        auto& v = tokens[i];
                        if(v == "x_min")
                            user_vars["x_min"] = default_x_min;
                        else if (v == "x_max")
                            user_vars["x_max"] = default_x_max;
                        else if (v == "samples")
                            user_vars["samples"] = default_samples;
                        else
                            user_vars.erase(v);
                    }
                }
            }
            else if (tokens.size() == 1 && tokens[0] == "lsv")
            {
                for (auto &v : user_vars)
                {
                    std::cout << v.first << " = " << v.second << std::endl;
                }
            }
            else if (tokens.size() == 3 && tokens[0] == "set")
            {
                user_vars[tokens[1]] = parser::Parser{tokens[2]}({});
            }
            else if (tokens.size() == 1 && tokens[0] == "plot")
            {
                plot::plot(functions, user_vars, user_vars["samples"], user_vars["x_min"], user_vars["x_max"]);
            }
            else if (tokens.size() == 1 && tokens[0] == "help")
            {
                std::cout << "help:\n\tdisplay this list\n"
                          << std::endl;
                std::cout << "add {function list}:\n\tadd one or more functions to the plotting list\n"
                          << std::endl;
                std::cout << "rm * | {index list}:\n\t remove all functions or just the one selected from the plotting list\n"
                          << std::endl;
                std::cout << "ls:\n\tshow the plotting list\n"
                          << std::endl;
                std::cout << "rmv * | {var list}:\n\t remove all vars or just the one selected from the var list\n"
                          << std::endl;
                std::cout << "lsv:\n\tshow the var list\n"
                          << std::endl;
                std::cout << "set <var> <expression>:\n\tset a var to a constant expression\n"
                          << std::endl;
                std::cout << "plot:\n\tplot all the functions in the plotting list\n"
                          << std::endl;
                std::cout << "exit:\n\tclose the program\n"
                          << std::endl;
            }
        }
    }
};
