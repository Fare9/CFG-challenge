//--------------------------------------------------------------------*- C++ -*-
// CFG: example of CFG
//
// @file test1.cpp
// @brief Test1 for testing simple Module, Function and BasicBlocks creation

#include "cfg/Module.hpp"

#include <memory>

int
main()
{
    std::unique_ptr<CFG::Module> M = std::make_unique<CFG::Module>("test1");

    auto Fn = CFG::Function::Create("Func1", M.get());

    auto BB1 = CFG::BasicBlock::Create("BB1", Fn);

    auto BB2 = CFG::BasicBlock::Create("BB2", Fn);

    std::cout << *M;

    Fn->delete_basic_block("BB2");

    std::cout << *M;

    M->delete_function(Fn);

    std::cout << *M;

    return 0;
}