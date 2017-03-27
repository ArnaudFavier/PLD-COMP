#ifndef _GLOBALDECLARATIONVARIABLE_H
#define _GLOBALDECLARATIONVARIABLE_H

#include "Declaration.h"
#include "MultipleDeclarationVariable.h"

class GlobalDeclarationVariable : public Declaration
{
public:
	GlobalDeclarationVariable(MultipleDeclarationVariable* _multipleDeclarationVariable);
	virtual string print() const;

private:
	MultipleDeclarationVariable* multipleDeclarationVariable;
};


#endif