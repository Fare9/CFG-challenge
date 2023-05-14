//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file BasicBlock.hpp
// @brief Basic blocks from the CFG

#ifndef BASICBLOCK_HPP
#define BASICBLOCK_HPP

#include <iostream>
#include <vector>
#include <string_view>
#include <cassert>
#include <fstream>

namespace CFG
{
    /// forward declaration to allow having
    /// a parent function
    class Function;

    /// @brief Class that represents a basic block
    /// in the CFG
    class BasicBlock
    {
        /// @brief Name for the basic block
        std::string name;
        /// @brief is entry block?
        bool entry_block{false};
        /// @brief is exit block?
        bool exit_block{false};
        /// @brief a start address
        std::uint64_t start_addr{0};
        /// @brief an end address
        std::uint64_t end_addr{0};
        /// @brief Parent function
        Function *parent_function;
        /// @brief Here we would write a vector for instructions...

    public:
        ~BasicBlock() = default;

        void set_entry_block(bool entry_block) { this->entry_block = entry_block; }

        bool get_entry_block() const { return entry_block; }

        void set_start_addr(std::uint64_t start_addr) { this->start_addr = start_addr; }

        std::uint64_t get_start_addr() const { return start_addr; }

        void set_end_addr(std::uint64_t end_addr) { this->end_addr = end_addr; }

        std::uint64_t get_end_addr() const { return end_addr; }

        const std::string &get_name() const { return name; }

        const Function *getParent() const { return parent_function; }

        Function *getParent() { return parent_function; }

        void dump_block_dot(std::ofstream &stream)
        {
            stream << "\"" << name
                   << "\" [shape=box, style=filled, fillcolor=lightgrey, label=\""
                   << "BB-" << name << "\"];\n\n";
        }

    private:
        BasicBlock(std::string_view Name, Function *Parent = nullptr);

    public:
        /// @brief Static function to create a new basic block
        /// @param Name name given to the basic block
        /// @param Parent parent function of the basic block
        /// @return pointer to a new allocated basic block
        static BasicBlock *Create(std::string_view Name = "", Function *Parent = nullptr)
        {
            assert(Parent && "Parent Function must be specified");

            return new BasicBlock(Name, Parent);
        }

        friend std::ostream &operator<<(std::ostream &os, const BasicBlock &bb)
        {
            os << "BB-" << bb.get_name() << "[start-addr=0x"
               << std::hex << bb.get_start_addr()
               << ", end-addr=0x" << bb.get_end_addr();
            if (bb.get_entry_block())
                os << ", entry-block";
            os << "]\n";
            return os;
        }
    };

} // namespace CFG

#endif