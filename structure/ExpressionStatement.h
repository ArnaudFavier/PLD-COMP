#ifndef _EXPRESSIONSTATEMENT_H
#define _EXPRESSIONSTATEMENT_H

#include "SimpleStatement.h"
#include "Expression.h"

class ExpressionStatement : public SimpleStatement
{
public:
    ExpressionStatement(Expression* _expr);

private:
    Expression* expr;
};

#endif