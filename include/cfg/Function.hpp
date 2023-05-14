//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file Function.hpp
// @brief Function for the CFG, Function contains blocks

#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include "cfg/BasicBlock.hpp"
#include "exceptions/noentryblock_exception.hpp"
#include "exceptions/noconnectedblock_exception.hpp"
#include "exceptions/multipleentryblock_exception.hpp"

#include <iostream>
#include <vector>
#include <string_view>
#include <memory>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <set>

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
        std::vector<BasicBlock *> basic_blocks;
        /// @brief Parent module
        Module *parent_module;

        using tag_bb_t = std::pair<std::string, BasicBlock *>;

        using edges_t = std::unordered_map<BasicBlock *, std::vector<tag_bb_t>>;

        /// @brief list of sucessors
        edges_t sucessors;

        std::unordered_map<BasicBlock *, std::vector<BasicBlock *>> predecessor;

        void delete_block_links(BasicBlock *bb)
        {
            for (auto pred : predecessor[bb])
            {
                /// get the list of sucessors from predecessors
                auto &pred_successors = sucessors[pred];

                /// look for the block to delete
                auto it = std::find_if(pred_successors.begin(), pred_successors.end(), [=](tag_bb_t &p)
                                       { return p.second == bb; });

                /// now delete the block from the list of its sucessors
                if (it != pred_successors.end())
                    pred_successors.erase(it);
            }
            /// now delete the sucessors
            sucessors.erase(bb);
        }

    public:
        ~Function()
        {
            for (auto bb : basic_blocks)
                delete bb;
            basic_blocks.clear();
        }

        const std::string &get_name() const { return name; }

        const std::vector<BasicBlock *> &get_basic_blocks() const { return basic_blocks; }

        void add_basic_block(BasicBlock *bb)
        {
            if (!basic_blocks.size())
                bb->set_entry_block(true);
            basic_blocks.push_back(bb);
        }

        BasicBlock *get_last_bb()
        {
            return basic_blocks.back();
        }

        bool delete_basic_block(BasicBlock *bb)
        {
            auto b = std::find(basic_blocks.begin(), basic_blocks.end(), bb);

            if (b == basic_blocks.end())
                return true;

            std::unique_ptr<BasicBlock> _(*b);

            delete_block_links(*b);

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

            delete_block_links(*b);

            basic_blocks.erase(b);

            return false;
        }

        /// @brief Add a sucessor block
        /// @param src block to include the sucessor
        /// @param dst destination block
        /// @param tag tag to include in the connection
        /// @return true in case there was an error, false other case
        bool add_sucessor(BasicBlock *src, BasicBlock *dst, std::string_view tag)
        {
            auto &vec = sucessors[src];

            auto it = std::find_if(vec.begin(), vec.end(),
                                   [=](tag_bb_t tag_bb)
                                   {
                                       return tag_bb.first == tag;
                                   });

            if (it != vec.end())
                return true;

            std::string tag_str = tag.data();

            vec.push_back({tag_str, dst});

            predecessor[dst].push_back(src);

            return false;
        }

        void dump_function_dot(std::ofstream &stream)
        {
            stream << "digraph \"" << name << "\"{\n";
            stream << "style=\"dashed\";\n";
            stream << "color=\"black\";\n";
            stream << "label=\"" << name << "\";\n";

            for (auto node : basic_blocks)
            {
                node->dump_block_dot(stream);
            }

            for (auto edge : sucessors)
            {
                auto src = edge.first;

                auto &vec = edge.second;

                for (auto succ : vec)
                {
                    auto &tag = succ.first;
                    auto dst = succ.second;
                    stream << "\"" << src->get_name() << "\" -> "
                           << "\"" << dst->get_name() << "\" [style=\"solid,bold\",color=black,weight=10,constraint=true,label=\""
                           << tag << "\"];\n";
                }
            }

            stream << "}";
        }

        void validate_function()
        {
            std::vector<BasicBlock *> todo;
            std::set<BasicBlock *> visited;

            if (basic_blocks.size() == 0)
                return;

            auto number_of_entry = std::count_if(basic_blocks.begin(), basic_blocks.end(), [](BasicBlock *bb)
                                                 { return bb->get_entry_block(); });

            if (number_of_entry == 0)
                throw exceptions::NoEntryBlockException("No entry block found on control flow graph");
            else if (number_of_entry > 1)
                throw exceptions::MultipleEntryBlockException("Multiple entry blocks found on control flow graph");

            todo.push_back(basic_blocks[0]);

            /// Depth First Search
            while (!todo.empty())
            {
                auto node = todo.back();
                todo.pop_back();

                if (visited.find(node) != visited.end())
                    continue;

                visited.insert(node);

                auto suces = sucessors[node];
                /// visit the nodes in reverse order for the sucessors
                for (auto suc = suces.rbegin(); suc != suces.rend(); ++suc)
                    todo.push_back(suc->second);
            }

            /// Once we have visited all the nodes following the DFS
            /// in this kind of graph we should have all the nodes
            /// visited if they have at least one connection
            if (basic_blocks.size() != visited.size())
                throw exceptions::NoConnectedBlockException("A node in the function is not connected to the control flow graph");
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