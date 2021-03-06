#include "DeclarationVariable.h"
#include "../middle_end/BasicBlock.h"
#include "../middle_end/CFG.h"
#include "../middle_end/IRRWMemory.h"
#include "../middle_end/Symbol.h"

DeclarationVariable::DeclarationVariable(char *_id, bool _array)
    : Printable(), id(_id), array(_array), declaration(true)
{
}

DeclarationVariable::DeclarationVariable(char *_id, bool _array, bool _declaration)
    : Printable(), id(_id), array(_array), declaration(_declaration)
{
}

DeclarationVariable::~DeclarationVariable()
{
    if (id != nullptr)
    {
        free(id);
    }
}

char *DeclarationVariable::getId()
{
    return id;
}

bool DeclarationVariable::isArray()
{
    return array;
}

bool DeclarationVariable::isDeclaration()
{
    return declaration;
}

std::string DeclarationVariable::toString() const
{
    if (!array)
    {
        return std::string(id);
    }
    return "ERROR_DeclarationVariable";
}

