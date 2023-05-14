//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file test2.cpp
// @brief Test2 for testing simple graphviz

#include "cfg/Module.hpp"

#include <iostream>
#include <fstream>
#include <memory>

int
main()
{
    std::unique_ptr<CFG::Module> M = std::make_unique<CFG::Module>("test1");

    auto Fn = CFG::Function::Create("Func1", M.get());

    auto Entry = CFG::BasicBlock::Create("Entry", Fn);

    auto H = CFG::BasicBlock::Create("H", Fn);

    auto I = CFG::BasicBlock::Create("I", Fn);

    auto J = CFG::BasicBlock::Create("J", Fn);


    Fn->add_sucessor(Entry, H, "true");
    Fn->add_sucessor(Entry, I, "false");
    Fn->add_sucessor(H, J, "");
    Fn->add_sucessor(I, J, "");

    if (Fn->add_sucessor(Entry, J, "true"))
    {
        std::cout << "It's not possible to create sucessor Entry->J with tag 'true'...";
        std::cout << "Test passed\n";
    }

    std::ofstream ofs{"graph.dot"};

    Fn->dump_function_dot(ofs);

    std::cout << "graph.dot generated\n";
    
    ofs.close();

    std::cout << "removing basic block H\n";

    Fn->delete_basic_block(H);

    ofs.open("graph2.dot");

    Fn->dump_function_dot(ofs);
    
    std::cout << "graph2.dot generated\n";

    ofs.close();

    auto K = CFG::BasicBlock::Create("K", Fn);

    Fn->add_sucessor(J, K, "loop");

    Fn->add_sucessor(K, J, "loop");

    ofs.open("graph3.dot");

    Fn->dump_function_dot(ofs);
    
    std::cout << "graph3.dot generated\n";

    ofs.close();

    return 0;
}