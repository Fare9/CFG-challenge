#include "cfg/Function.hpp"
#include "cfg/Module.hpp"

using namespace CFG;

Function *Function::Create(std::string_view Name, Module *Parent)
{
    assert(Parent && "Parent Module must be specified");

    Parent->add_function(std::make_unique<Function>(Name, Parent));

    return Parent->get_last_function();
}