#include "BinaryOperatorExpression.h"
#include "../comp.tab.h"
#include "../middle_end/CFG.h"
#include "../middle_end/IRBinaryOp.h"

BinaryOperatorExpression::BinaryOperatorExpression(Expression* _left, Expression* _right, int _op)
    :Expression(),left(_left),right(_right),op(_op)
{
    int type1 = _left->getType();
    int type2 = _right->getType();

    if (isArrayType(type1) != isArrayType(type2))
    {
        setType(EXPRESSION_TYPE_CONFLICT);
    }
    else if(sizeOfType(type1) > sizeOfType(type2))
    {
        setType(type1);
    }
    else
    {
        setType(type2);
    }
}

BinaryOperatorExpression::BinaryOperatorExpression(Expression* _expr1, Expression* _expr2, int _op, int _type)
    :Expression(),left(_expr1),right(_expr2),op(_op)
{
    setType(_type);
}

BinaryOperatorExpression::~BinaryOperatorExpression()
{
    if(left != nullptr)
    {
        delete left;
    }
    if(right != nullptr)
    {
        delete right;
    }
}

std::string BinaryOperatorExpression::toString() const
{
    std::string txt = "(" + left->toString();

    switch(op)
    {
    case COMMA:
        txt += " , ";
        break;
    case EQUAL_EQUAL:
        txt += " == ";
        break;
    case DIFF:
        txt += " != ";
        break;
    case LESS_THAN:
        txt += " < ";
        break;
    case LESS_THAN_OR_EQUAL:
        txt += " <= ";
        break;
    case MORE_THAN:
        txt += " > ";
        break;
    case MORE_THAN_OR_EQUAL:
        txt += " >= ";
        break;
    case AND_AND:
        txt += " && ";
        break;
    case OR_OR:
        txt += " || ";
        break;
    case MUL:
        txt += " * ";
        break;
    case DIV:
        txt += " / ";
        break;
    case MOD:
        txt += " % ";
        break;
    case PLUS:
        txt += " + ";
        break;
    case MINUS:
        txt += " - ";
        break;
    case AND:
        txt += " & ";
        break;
    case OR:
        txt += " | ";
        break;
    case POW:
        txt += " ^ ";
        break;
    case LEFT_DEC:
        txt += " << ";
        break;
    case RIGHT_DEC:
        txt += " >> ";
        break;
    default:
        return "ERROR_BinaryOperatorExpression";
    }
    return txt + right->toString() + ")";
}

void BinaryOperatorExpression::buildIR(CFG *cfg) const
{
    IRBinaryOp * instruction = nullptr;
    Symbol * expr1Symbol = nullptr;
    ExpressionVariable *variable = dynamic_cast<ExpressionVariable *>(left);
    if(variable != nullptr)
    {
        expr1Symbol = cfg->getCurrentBasicBlock()->getSymbol(variable->getId());
    }
    else
    {
        left->buildIR(cfg);
        expr1Symbol = cfg->getLastInstructionDestination();
    }

    Symbol * expr2Symbol = nullptr;
    variable = dynamic_cast<ExpressionVariable *>(right);
    if(variable != nullptr)
    {
        expr2Symbol = cfg->getCurrentBasicBlock()->getSymbol(variable->getId());
    }
    else
    {
        right->buildIR(cfg);
        expr2Symbol = cfg->getLastInstructionDestination();
    }

    if(expr1Symbol != nullptr && expr2Symbol != nullptr)
    {
        Symbol * destination = new Symbol(cfg->getTempVariableName(),getType(),cfg->getOffsetFromCurrentBasicBlock());

        switch(op)
        {
        case COMMA:
            left->buildIR(cfg);
            right->buildIR(cfg);
            break;
        case EQUAL_EQUAL:
            // " == ";
            break;
        case DIFF:
            // " != ";
            break;
        case LESS_THAN:
            // " < ";
            break;
        case LESS_THAN_OR_EQUAL:
            // " <= ";
            break;
        case MORE_THAN:
            // " > ";
            break;
        case MORE_THAN_OR_EQUAL:
            // " >= ";
            break;
        case AND_AND:
            // " && ";
            break;
        case OR_OR:
            // " || ";
            break;
        case MUL:
            instruction = new IRBinaryOp(IRBinaryOp::Type::MUL,destination,expr1Symbol,expr2Symbol);
            break;
        case DIV:
            instruction = new IRBinaryOp(IRBinaryOp::Type::DIV,destination,expr1Symbol,expr2Symbol);
            break;
        case MOD:
            instruction = new IRBinaryOp(IRBinaryOp::Type::MOD,destination,expr1Symbol,expr2Symbol);
            break;
        case PLUS:
            instruction = new IRBinaryOp(IRBinaryOp::Type::ADD,destination,expr1Symbol,expr2Symbol);
            break;
        case MINUS:
            instruction = new IRBinaryOp(IRBinaryOp::Type::SUB,destination,expr1Symbol,expr2Symbol);
            break;
        case AND:
            // " & ";
            break;
        case OR:
            // " | ";
            break;
        case POW:
            // " ^ ";
            break;
        case LEFT_DEC:
            // " << ";
            break;
        case RIGHT_DEC:
            // " >> ";
            break;
        }

        if(instruction != nullptr)
        {
            cfg->addInstructionInCurrentBasicBlock(instruction);
        }
    }
}

Expression *BinaryOperatorExpression::getLeft() const
{
    return left;
}

Expression *BinaryOperatorExpression::getRight() const
{
    return right;
}

