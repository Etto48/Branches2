#include "integration.hpp"

namespace Branches::integration
{
    constexpr core::data_t one_plus = 1.00001;
    core::data_t integrate(double from, double to, parser::Parser& p, const std::string& var, core::variables_t user_vars)
    {
        double samples = user_vars.find("samples")->second.real();
        double range_size = to - from;
        double step = range_size/samples;

        std::vector<core::data_t> x;
        unsigned usamples = (unsigned)std::abs(int(samples));

        core::data_t ret = 0;

        x.reserve(usamples);
        for (unsigned i = 0; i < usamples; i++)
            x.push_back(double(i)*step+from);
        
        std::map<std::string,core::data_t> vars = {{var,0}};
        vars.insert(user_vars.begin(),user_vars.end());
        for (auto& px : x)
        {
            vars[var]=px;    
            ret += step * p(vars);
        }
        return ret;
    }
    std::vector<core::data_t> sft(parser::Parser& p, core::variables_t user_vars)
    {
        double to = user_vars.find("x_max")->second.real();
        double from = user_vars.find("x_min")->second.real();
        double samples = user_vars.find("samples")->second.real();
        double range_size = to - from;
        double step = range_size/samples;
        
        parser::Parser int_argument{"("+p.get_source()+")*exp(-2j*pi*f*t)"};
        std::vector<double> f;
        unsigned usamples = (unsigned)std::abs(int(samples));
        f.reserve(usamples);
        for(unsigned i = 0; i < usamples; i++)
            f.push_back(double(i)*step+from);
        
        std::vector<core::data_t> y;
        y.reserve(usamples);
        std::map<std::string,core::data_t> vars = {{"f",0}};
        vars.insert(user_vars.begin(),user_vars.end());
        double interval = samples / 20;
        for(auto& fp : f)
        {
            vars["f"]=fp;  
            y.push_back(integrate(-interval,interval,int_argument,"t",vars));
        }
        return y;
    }
    std::vector<core::data_t> isft(parser::Parser& p, core::variables_t user_vars)
    {
        parser::Parser int_argument{"("+p.get_source()+")*exp(2j*pi*f*t)"};
        return {};
    }
}