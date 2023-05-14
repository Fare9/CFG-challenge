//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file Function.hpp
// @brief Function for the CFG, Function contains blocks

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "cfg/BasicBlock.hpp"

#include <iostream>
#include <vector>
#include <string_view>
#include <memory>
#include <cassert>
#include <algorithm>

namespace CFG
{
    /// forward declaration to allow having a Module
    /// as parent of the function
    class Module;

    class Function
    {
        /// @brief Name for the function
        std::string name;
        /// @brief Vector of unique pointers of basic blocks
        std::vector<BasicBlock*> basic_blocks;
        /// @brief Parent module
        Module *parent_module;

    public:
        ~Function()
        {
            for (auto bb : basic_blocks)
                delete bb;
            basic_blocks.clear();
        }

        const std::string &get_name() const { return name; }

        const std::vector<BasicBlock*> &get_basic_blocks() const { return basic_blocks; }

        void add_basic_block(BasicBlock* bb)
        {
            if (!basic_blocks.size())
                bb->set_entry_block(true);
            basic_blocks.push_back(bb);
        }

        BasicBlock *get_last_bb()
        {
            return basic_blocks.back();
        }

        bool delete_basic_block(BasicBlock * bb)
        {
            auto b = std::find(basic_blocks.begin(), basic_blocks.end(), bb);

            if (b == basic_blocks.end())
                return true;
            
            std::unique_ptr<BasicBlock> _(*b);

            basic_blocks.erase(b);

            return false;
        }

        bool delete_basic_block(std::string_view name)
        {
            auto b = std::find_if(basic_blocks.begin(), basic_blocks.end(), 
                [=](BasicBlock *b)
                {
                    return b->get_name() == name;
                });

            if (b == basic_blocks.end())
                return true;
            
            std::unique_ptr<BasicBlock> _(*b);

            basic_blocks.erase(b);

            return false;
        }

    private:
        Function(std::string_view Name, Module *Parent = nullptr);

    public:
        static Function *Create(std::string_view Name, Module *Parent = nullptr)
        {
            assert(Parent && "Parent Module must be specified");

            return new Function(Name, Parent);
        }

        friend std::ostream &operator<<(std::ostream &os, const Function &func)
        {
            os << "Function-" << func.get_name() << "\n";
            for (const auto &bb : func.get_basic_blocks())
                os << "\t" << *bb;
            return os;
        }
    };
} // namespace CFG

#endif