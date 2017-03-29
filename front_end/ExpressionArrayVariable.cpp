#include "ExpressionArrayVariable.h"

ExpressionArrayVariable::ExpressionArrayVariable(char* _id, Expression* _expr, int _type)
	:ExpressionVariable(_type),id(_id),expr(_expr)
{
    setExpressionType(EXPRESSION_ARRAY_VARIABLE);
}

ExpressionArrayVariable::~ExpressionArrayVariable()
{
	if(id != nullptr)
	{
		delete id;
	}
	if(expr != nullptr)
	{
		delete expr;
	}
}

string ExpressionArrayVariable::toString() const
{
	return string(id) + "[" + expr->toString() + "]";
}
