
#include "cfg/BasicBlock.hpp"
#include "cfg/Function.hpp"

using namespace CFG;

BasicBlock::BasicBlock(std::string_view Name, Function *Parent) : name(Name), parent_function(Parent)
{
    Parent->add_basic_block(this);
}