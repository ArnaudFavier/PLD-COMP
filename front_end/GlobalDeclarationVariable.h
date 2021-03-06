#ifndef _GLOBALDECLARATIONVARIABLE_H
#define _GLOBALDECLARATIONVARIABLE_H

#include "Declaration.h"
#include "MultipleDeclarationVariable.h"

class GlobalDeclarationVariable : public Declaration
{
public:
	GlobalDeclarationVariable(MultipleDeclarationVariable* _multipleDeclarationVariable);
	virtual ~GlobalDeclarationVariable();

    virtual std::string toString() const;
    virtual void buildIR(CFG * cfg) const;

    MultipleDeclarationVariable* getMultipleDeclarationVariable();
private:
	MultipleDeclarationVariable* multipleDeclarationVariable;
};


#endif
