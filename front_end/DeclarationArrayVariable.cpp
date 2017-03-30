#include "DeclarationArrayVariable.h"

DeclarationArrayVariable::DeclarationArrayVariable(char* _id, int _size)
	: DeclarationVariable(_id, true, true), size(_size)
{

}

DeclarationArrayVariable::~DeclarationArrayVariable()
{

}

string DeclarationArrayVariable::toString() const
{
	if(array) 
	{
		return string(id) + "[" + string(id) + "]";
	} 
	return "ERROR_DeclarationArrayVariable";
}