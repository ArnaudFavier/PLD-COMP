#include "ExpressionArrayVariable.h"

ExpressionArrayVariable::ExpressionArrayVariable(char* _id, Expression* _expr, int _type)
	:ExpressionVariable(_type),id(_id),expr(_expr)
{
    setExpressionType(EXPRESSION_ARRAY_VARIABLE);
}

ExpressionArrayVariable::~ExpressionArrayVariable()
{
    delete expr;
}

string ExpressionArrayVariable::toString() const
{
	return string(id) + string("[") + expr->toString() + string("]");
}