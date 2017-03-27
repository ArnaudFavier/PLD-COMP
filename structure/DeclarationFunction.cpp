#include "DeclarationFunction.h"

DeclarationFunction::DeclarationFunction(Type* _type, char* _id, ArgumentList* _argumentList, DeclarationFunctionStatement* _decFunctionStatement)
	: Declaration() ,type(_type), id(_id), argumentList(_argumentList), decFunctionStatement(_decFunctionStatement)
{

}

string DeclarationFunction::print() const
{
	return "DeclarationFunction";
}