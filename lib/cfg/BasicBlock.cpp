
#include "cfg/BasicBlock.hpp"
#include "cfg/Function.hpp"

namespace CFG
{
    BasicBlock *BasicBlock::Create(std::string_view Name, Function *Parent)
    {
        assert(Parent && "Parent Function must be specified");

        Parent->add_basic_block(std::make_unique<BasicBlock>(Name, Parent));

        return Parent->get_last_bb();
    }
}