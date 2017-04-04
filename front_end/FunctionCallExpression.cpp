#include "FunctionCallExpression.h"
#include "../middle_end/CFG.h"
#include "../middle_end/IRCall.h"
#include <vector>

#include "../comp.tab.h"

FunctionCallExpression::FunctionCallExpression(char* _id, Expression* _expr, int _type)
    : Expression(), id(_id), expr(_expr)
{

    type = _type;
}

FunctionCallExpression::~FunctionCallExpression()
{
    if(id != nullptr)
    {
        free(id);
    }
    if(expr != nullptr)
    {
        delete expr;
    }
}

std::string FunctionCallExpression::toString() const
{

    std::string exprStr = "";
    if(expr != nullptr)
    {
        exprStr = expr->toString();
    }
    return std::string(id) + "(" + exprStr + ")";
}

void FunctionCallExpression::buildIR(CFG *cfg) const
{
    IRCall * instruction;

    Symbol * returnSymbol = nullptr;

    if(getType() != VOID)
    {
        returnSymbol = new Symbol(cfg->getTempVariableName(),getType(),cfg->getOffsetFromCurrentBasicBlock());
    }

    instruction = new IRCall(id,returnSymbol,getType() == VOID);

    // On ajoute les params
    if(expr != nullptr)
    {
        BinaryOperatorExpression* binaryExpr = dynamic_cast<BinaryOperatorExpression*>(expr);
        Expression * next = expr;

        std::vector<const Symbol *> vectorParameters;

        while(binaryExpr != nullptr)
        {
            binaryExpr->getRight()->buildIR(cfg);

            const Symbol * param = cfg->getLastInstructionDestination();
            vectorParameters.push_back(param);

            std::cout << param->getName() << std::endl;

            next = binaryExpr;
            binaryExpr = dynamic_cast<BinaryOperatorExpression*>(binaryExpr->getLeft());
        }

        next->buildIR(cfg);
        const Symbol * param = cfg->getLastInstructionDestination();
        vectorParameters.push_back(param);

        for(int i = vectorParameters.size()-1; i >= 0; --i)
        {
            instruction->addParameter(vectorParameters[i]);
        }

    }

    cfg->addInstructionInCurrentBasicBlock(instruction);
}
