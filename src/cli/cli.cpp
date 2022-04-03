#include "cli.hpp"

namespace Branches::cli
{
    constexpr core::data_t default_samples = 2000, default_x_min = -5, default_x_max = 5, default_y_min = -5, default_y_max = 5;
    std::map<std::string, Branches::core::data_t> user_vars =
        {
            {"x_min", default_x_min},
            {"x_max", default_x_max},
            {"samples", default_samples},
            {"y_min", default_y_min},
            {"y_max", default_y_max},
    };
    std::map<std::string, Branches::core::data_t> default_user_vars = user_vars;
    std::vector<Branches::parser::Parser> functions;
    bool error = false;
    std::string prompt()
    {
        return std::string{error ? "\033[1;31mX\033[0m" : "\033[1;32mO\033[0m"} + " Functions: " + std::to_string(functions.size()) + ", Vars: " + std::to_string(user_vars.size()) + " \033[1;35m>>\033[0m ";
    }

    std::vector<std::string> split_command(const std::string &cmd)
    {
        std::stringstream ss{cmd};
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
            try
            {
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
                        user_vars = default_user_vars;
                    }
                    else
                    {
                        for (unsigned i = 1; i < tokens.size(); i++)
                        {
                            auto &v = tokens[i];
                            if (default_user_vars.find(v) != default_user_vars.end())
                                user_vars[v] = default_user_vars[v];
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
                else if (tokens.size() >= 1 && tokens[0] == "plot")
                {
                    bool complex_out = false;
                    bool complex_in = false;
                    for(auto& t: tokens)
                    {
                        if(t=="complex_out")
                            complex_out = true;
                        else if(t=="complex_in")
                            complex_in = true;
                        else if(t=="complex")
                        {
                            complex_in = complex_out = true;
                        }
                    }
                    if(complex_in)
                        plot::plot_complex(functions, user_vars, complex_out);
                    else
                        plot::plot(functions, user_vars, complex_out);
                }
                else if (tokens.size() == 3 && tokens[0] == "derivative")
                {
                    std::cout << parser::Parser(tokens[1]).derivative(tokens[2]) << std::endl;
                }
                else if (tokens.size() == 2 && tokens[0] == "fourier")
                {
                    auto p = parser::Parser{tokens[1]};
                    plot::plot_ft(p, user_vars);
                }
                else if (tokens.size() == 2 && tokens[0] == "ifourier")
                {
                    auto p = parser::Parser{tokens[1]};
                    plot::plot_ift(p, user_vars);
                }
                else if (tokens.size() == 1 && tokens[0] == "help")
                {
                    std::cout << "help:\n\tdisplay this list\n"
                              << std::endl;
                    std::cout << "add {f(x) list}:\n\tadd one or more functions to the plotting list\n"
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
                    std::cout << "plot [complex]:\n\tplot all the functions in the plotting list, (use complex to plot also the imaginary part)\n"
                              << std::endl;
                    std::cout << "derivative <f(<k>)> <k>:\n\tprint the partial derivative of f in k\n"
                              << std::endl;
                    std::cout << "fourier <x(t)>:\n\tplot the fourier transform of x\n"
                              << std::endl;
                    std::cout << "ifourier <X(f)>:\n\tplot the inverse fourier transform of X\n"
                              << std::endl;
                    std::cout << "exit:\n\tclose the program\n"
                              << std::endl;
                }
                else if(tokens.size() == 0)
                {
                    continue;
                }
                else
                {
                    error = true;
                    continue;
                }
                error = false;
            }
            catch (exceptions::Error &e)
            {
                std::cout << "\033[1;31m" << e.what() << "\033[0m" << std::endl;
                error = true;
            }
        }
    }
};
