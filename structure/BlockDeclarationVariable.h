#ifndef _BLOCKDECLARATIONVARIABLE_H
#define _BLOCKDECLARATIONVARIABLE_H

#include "SimpleStatement.h"
#include "MultipleDeclarationVariable.h"

// Declaration de variable dans un block
class BlockDeclarationVariable : public SimpleStatement
{
public:
    BlockDeclarationVariable(MultipleDeclarationVariable* _multipleDeclarationVariable);
    virtual string print();
    MultipleDeclarationVariable* getMultipleDeclarationVariable();

private:
    MultipleDeclarationVariable* multipleDeclarationVariable;
};

#endif
