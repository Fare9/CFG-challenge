//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file Module.hpp
// @brief Module for the CFG, a Module contain Functions

#ifndef MODULE_HPP
#define MODULE_HPP

#include "cfg/Function.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

namespace CFG
{
    class Module
    {
        /// @brief Name of the module
        std::string name;
        /// @brief Vector with functions
        std::vector<Function*> functions;

    public:
        ~Module()
        {
            for (auto func : functions)
                delete func;
            functions.clear();
        }

        Module(std::string_view Name) : name(Name) {}

        const std::string &get_name() const { return name; }

        const std::vector<Function*> &get_functions() const
        {
            return functions;
        }

        bool delete_function(Function * func)
        {
            auto f = std::find(functions.begin(), functions.end(), func);

            if (f == functions.end())
                return true;
            
            std::unique_ptr<Function> _(*f);

            functions.erase(f);

            return false;
        }

        bool delete_function(std::string_view name)
        {
            auto f = std::find_if(functions.begin(), functions.end(), 
                [=](Function *f)
                {
                    return f->get_name() == name;
                });

            if (f == functions.end())
                return true;
            
            std::unique_ptr<Function> _(*f);

            functions.erase(f);

            return false;
        }

        void add_function(Function* func)
        {
            functions.push_back(func);
        }

        Function *get_last_function()
        {
            return functions.back();
        }

        friend std::ostream &operator<<(std::ostream &os, const Module &mod)
        {
            os << "Module-" << mod.get_name() << "\n";
            for (const auto& func : mod.get_functions())
                os << *func;
            return os;
        }


    };
} // namespace CFG

#endif