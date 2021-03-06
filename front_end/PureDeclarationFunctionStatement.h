#ifndef _PUREDECLARATIONFUNCTIONSTATEMENT_H
#define _PUREDECLARATIONFUNCTIONSTATEMENT_H

#include "DeclarationFunctionStatement.h"

// Declaration sans initialisation de la fonction
class PureDeclarationFunctionStatement : public DeclarationFunctionStatement
{
public:
	PureDeclarationFunctionStatement();
	virtual ~PureDeclarationFunctionStatement();

    virtual std::string toString() const;
    virtual void buildIR(CFG * cfg) const;
};

#endif
