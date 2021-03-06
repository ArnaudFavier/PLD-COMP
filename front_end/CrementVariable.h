#ifndef _CREMENTIALVARIABLE_H
#define _CREMENTIALVARIABLE_H

#include "Expression.h"
#include "ExpressionVariable.h"

class CrementVariable : public Expression 
{
public:
	CrementVariable(ExpressionVariable* _exprVar, bool _increment, bool _preCrement);
	virtual ~CrementVariable();

    virtual std::string toString() const;
    virtual void buildIR(CFG* cfg) const;

private:
	ExpressionVariable* exprVar;
	// Si faux, decrement
	bool increment;
	// Si faux, post-crement
	bool preCrement;
};

#endif
