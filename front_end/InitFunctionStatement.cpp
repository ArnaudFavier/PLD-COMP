#include "InitFunctionStatement.h"

InitFunctionStatement::InitFunctionStatement(MultipleStatement* _multipleStatement)
    : DeclarationFunctionStatement(false), multipleStatement(_multipleStatement)
{

}

InitFunctionStatement::~InitFunctionStatement()
{
    delete multipleStatement;
}

string InitFunctionStatement::toString() const
{
	return string("{") + multipleStatement->toString() + string("}");
}

int InitFunctionStatement::countStatements()
{
    return multipleStatement->countStatements();
}

SimpleStatement*& InitFunctionStatement::operator[] (int i)
{
    return (*multipleStatement)[i];
}