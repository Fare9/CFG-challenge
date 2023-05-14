//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file test3.cpp
// @brief Test3 for testing validation of function control flow graph

#include "cfg/Module.hpp"

#include <iostream>
#include <fstream>
#include <memory>

int
main()
{
    std::unique_ptr<CFG::Module> M = std::make_unique<CFG::Module>("test3");

    /// correct function, this should work correctly
    auto Fn = CFG::Function::Create("Func1", M.get());
    auto Entry = CFG::BasicBlock::Create("Entry", Fn);
    auto H = CFG::BasicBlock::Create("H", Fn);
    auto I = CFG::BasicBlock::Create("I", Fn);
    auto J = CFG::BasicBlock::Create("J", Fn);
    Fn->add_sucessor(Entry, H, "true");
    Fn->add_sucessor(Entry, I, "false");
    Fn->add_sucessor(H, J, "");
    Fn->add_sucessor(I, J, "");

    try
    {
        Fn->validate_function();
        std::cout << "Function " << Fn->get_name() << " is correct.\n";
    }catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }

    /// A function with two entry blocks
    auto Fn2 = CFG::Function::Create("Func2", M.get());
    auto Entry2 = CFG::BasicBlock::Create("Entry", Fn2);
    auto FakeEntry = CFG::BasicBlock::Create("FakeEntry", Fn2);
    FakeEntry->set_entry_block(true);
    Fn->add_sucessor(Entry2, FakeEntry, "");
    
    try
    {
        Fn2->validate_function();
        std::cout << "Function " << Fn2->get_name() << " is correct.\n";
    }catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }

    /// A node with no connection

    auto Fn3 = CFG::Function::Create("Func3", M.get());
    auto Entry3 = CFG::BasicBlock::Create("Entry", Fn3);
    auto H2 = CFG::BasicBlock::Create("H", Fn3);
    auto I2 = CFG::BasicBlock::Create("I", Fn3);
    auto J2 = CFG::BasicBlock::Create("J", Fn3);
    Fn3->add_sucessor(Entry3, H2, "true");
    Fn3->add_sucessor(Entry3, I2, "false");
    /// Node J2 not reachable
    ///Fn->add_sucessor(H2, J2, "");
    ///Fn->add_sucessor(I2, J2, "");
    try
    {
        Fn3->validate_function();
        std::cout << "Function " << Fn3->get_name() << " is correct.\n";
    }catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }

    /// A function with no entry block
    auto Fn4 = CFG::Function::Create("Func4", M.get());
    auto Entry4 = CFG::BasicBlock::Create("Entry", Fn4);
    Entry4->set_entry_block(false);

    try
    {
        Fn4->validate_function();
        std::cout << "Function " << Fn4->get_name() << " is correct.\n";
    }catch (std::exception & e)
    {
        std::cerr << e.what() << "\n";
    }
}