#include "ExpressionStatement.h"

ExpressionStatement::ExpressionStatement(Expression* _expr)
    : SimpleStatement(), expr(_expr)
{

}