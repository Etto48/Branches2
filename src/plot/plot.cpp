#include "plot.hpp"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
namespace Branches::plot
{
    void plot(std::vector<parser::Parser>& functions, core::variables_t user_vars, bool complex_out)
    {
        double to = user_vars.find("x_max")->second.real();
        double from = user_vars.find("x_min")->second.real();
        double samples = user_vars.find("samples")->second.real();
        double max = user_vars.find("y_max")->second.real();
        double min = user_vars.find("y_min")->second.real();
        double range_size = to - from;
        double step = range_size/samples;

        std::vector<double> x;
        unsigned usamples = (unsigned)std::abs(int(samples));
        
        x.reserve(usamples);
        for (unsigned i = 0; i < usamples; i++)
            x.push_back(i*step+from);

        plt::axvline(0,{{"color","dimgray"}});
        plt::axhline(0,{{"color","dimgray"}});
        plt::grid();
        plt::tight_layout();
        
        std::map<std::string,core::data_t> vars = {{"x",0}};
        vars.insert(user_vars.begin(),user_vars.end());
        for(auto& f : functions)
        {
            std::vector<double> y_r;
            std::vector<double> y_i;
            y_r.reserve(usamples);
            if(complex_out)
                y_i.reserve(usamples);
            for(auto& px : x)
            {
                vars["x"]=px;
                core::data_t new_val = f(vars);
                if(new_val.real() >= min && new_val.real() <= max)
                    y_r.push_back(new_val.real());
                else 
                    y_r.push_back(nan(" "));
                if(complex_out)
                    y_i.push_back(new_val.imag());
            }
            if(!complex_out)
                plt::plot(x,y_r,{{"label",f.get_source()}});           
            else
            {
                plt::plot(x,y_i,{{"label","Im{"+f.get_source()+"}"}});           
                plt::plot(x,y_r,{{"label","Re{"+f.get_source()+"}"}});           
            }
        }
        if(functions.size())
            plt::legend();
        plt::show();
    }
    void plot_complex(std::vector<parser::Parser>& functions, core::variables_t user_vars, bool complex_out)
    {
        double to = user_vars.find("x_max")->second.real();
        double from = user_vars.find("x_min")->second.real();
        double samples = std::sqrt(user_vars.find("samples")->second.real());
        double max = user_vars.find("y_max")->second.real();
        double min = user_vars.find("y_min")->second.real();
        double range_size = to - from;
        double step = range_size/samples;

        std::vector<double> y;
        std::vector<std::vector<double>> xx, yy;

        unsigned usamples = (unsigned)std::abs(int(samples));
        
        y.reserve(usamples);
        for (unsigned i = 0; i < usamples; i++)
        {
            y.push_back(i*step+from);
        }

        xx.reserve(usamples);
        yy.reserve(usamples);
        for(unsigned i = 0; i < usamples; i++)
        {
            xx.push_back(std::vector<double>(usamples,i*step+from));
            yy.push_back(y);
        }
        
        std::map<std::string,core::data_t> vars = {{"z",0}};
        vars.insert(user_vars.begin(),user_vars.end());

        for(auto& f : functions)
        {    
            std::vector<std::vector<double>> z_r(usamples);
            std::vector<std::vector<double>> z_i(complex_out?usamples:0);
            for(unsigned x = 0; x < usamples; x++)
            {
                z_r[x].reserve(usamples);
                if(complex_out)
                    z_i[x].reserve(usamples);
                for(unsigned y = 0; y < usamples; y++)
                {
                    vars["z"]=core::data_t{xx[x][y],yy[x][y]};
                    z_r[x].push_back(f(vars).real());
                    if(complex_out)
                        z_i[x].push_back(f(vars).imag());
                }
            }
            plt::plot_surface(xx,yy,z_r);
            plt::title("Re{"+f.get_source()+"}");
            plt::xlabel("real");
            plt::ylabel("imag");
            if(complex_out)
            {
                plt::plot_surface(xx,yy,z_i);
                plt::title("Im{"+f.get_source()+"}");
                plt::xlabel("real");
                plt::ylabel("imag");
            }
        }
        plt::show();
    }
    void plot_ft(parser::Parser& p, core::variables_t user_vars)
    {
        double to = user_vars.find("x_max")->second.real();
        double from = user_vars.find("x_min")->second.real();
        double samples = user_vars.find("samples")->second.real();
        double max = user_vars.find("y_max")->second.real();
        double min = user_vars.find("y_min")->second.real();
        double range_size = to - from;
        double step = range_size/samples;

        std::vector<double> x;
        unsigned usamples = (unsigned)std::abs(int(samples));
        x.reserve(usamples);
        for (unsigned i = 0; i < usamples; i++)
            x.push_back(i*step+from);

        plt::axvline(0,{{"color","dimgray"}});
        plt::axhline(0,{{"color","dimgray"}});
        plt::grid();
        plt::tight_layout();
        
        std::vector<double> y_r;
        std::vector<double> y_i;
        y_r.reserve(usamples);
        y_i.reserve(usamples);

        auto y = integration::sft(p,user_vars);
        for(auto& py : y)
        {
            y_r.push_back(py.real());
            y_i.push_back(py.imag());
        }
        plt::plot(x,y_i,{{"label","Im"}});
        plt::plot(x,y_r,{{"label","Re"}});
        plt::legend();
        plt::show();
    }
    void plot_ift(parser::Parser& p, core::variables_t user_vars)
    {
        double to = user_vars.find("x_max")->second.real();
        double from = user_vars.find("x_min")->second.real();
        double samples = user_vars.find("samples")->second.real();
        double max = user_vars.find("y_max")->second.real();
        double min = user_vars.find("y_min")->second.real();
        double range_size = to - from;
        double step = range_size/samples;

        std::vector<double> x;
        unsigned usamples = (unsigned)std::abs(int(samples));
        x.reserve(usamples);
        for (unsigned i = 0; i < usamples; i++)
            x.push_back(i*step+from);

        plt::axvline(0,{{"color","dimgray"}});
        plt::axhline(0,{{"color","dimgray"}});
        plt::grid();
        plt::tight_layout();
        
        std::vector<double> y_r;
        std::vector<double> y_i;
        y_r.reserve(usamples);
        y_i.reserve(usamples);

        auto y = integration::isft(p,user_vars);
        for(auto& py : y)
        {
            y_r.push_back(py.real());
            y_i.push_back(py.imag());
        }
        plt::plot(x,y_i,{{"label","Im"}});
        plt::plot(x,y_r,{{"label","Re"}});
        plt::legend();
        plt::show();
    }
}

