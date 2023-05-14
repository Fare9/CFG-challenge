#include "cfg/Function.hpp"
#include "cfg/Module.hpp"

using namespace CFG;

Function::Function(std::string_view Name, Module *Parent) : name(Name), parent_module(Parent)
{
    Parent->add_function(this);
}