#include "CFG.h"

#include "../front_end/Genesis.h"
#include "../front_end/Declaration.h"
#include "../front_end/GlobalDeclarationVariable.h"
#include "../front_end/DeclarationFunction.h"

#include "IRInstruction.h"
#include "IRConditionnal.h"
#include "BasicBlock.h"
#include "Parser.h"


CFG::CFG(const Parser * parser, DeclarationFunction * _function) :
    nextBBnumber(0), lastBasicBlockLevel(0), maximalOffset(1),
    function(_function), currentBasicBlock(nullptr)
{
    // Toujours avant de faire buildIR !
    LevelData levelZeroData;
    mapLevelData.insert(std::pair<int,LevelData>(0,levelZeroData));

    symbolsTable = parser->getGlobalSymbolTable();
    _function->buildIR(this);
}

CFG::CFG() : function(nullptr)
{
}

std::string CFG::toString() const
{
    std::string s = "===== " + this->getName() + " =====\n";

    BasicBlock * current = rootBasicBlock;

    while(current != currentBasicBlock)
    {
        s += current->toString();
        std::cout << s << std::endl;
        if(current->getInstructions().size() != 0)
        {
            IRInstruction * instruction = current->getInstructions().back();
            if(instruction->getOperation() == IRInstruction::Operation::CONDITIONNAL)
            {
                current = dynamic_cast<IRConditionnal*>(instruction)->getBlockEnd();
            }
            else
            {
                current = current->getExitTrue();
            }
        }
        else
        {
            current = current->getExitTrue();
        }
    }
    if(currentBasicBlock != nullptr)
    {
        s += current->toString();
    }
    return s;
}

BasicBlock * CFG::createNewBasicBlock(int level, std::string bbName)
{
    BasicBlock * bb = new BasicBlock(level,this,bbName);

    if(level < lastBasicBlockLevel)
    {
        cleanLevel(lastBasicBlockLevel);
    }

    lastBasicBlockLevel = level;

    return bb;
}

BasicBlock * CFG::createNewBasicBlock(int level)
{
    return createNewBasicBlock(level,getUsableBasicBlockName());
}

void CFG::addSymbol(Symbol *symbol)
{

    if (symbol != nullptr)
    {
        symbolsTable.insert(std::pair<std::string, Symbol*>(symbol->getName(), symbol));
    }
}

Symbol* CFG::getSymbol(std::string name) const
{
    auto it = symbolsTable.find(name);
    if (it != symbolsTable.end())
        return it->second;
    else
        return nullptr;
}

void CFG::setLastBasicBlockFromLevel(int level, BasicBlock *block)
{
    auto pair = mapLevelData.find(level);

    if(pair != mapLevelData.end())
    {
        pair->second.lastBasicBlock = block;
    }
    else
    {
        std::cout << "Error CFG::setLastBasicBlockFromLevel no data for current level "
                  << std::to_string(level) << std::endl;
    }
}

const std::map <std::string, Symbol*> & CFG::getSymbolsTable() const
{
    return symbolsTable;
}


std::string CFG::getName() const
{
    if(function != nullptr)
        return function->getId();
    return "undefined";
}

std::string CFG::getUsableBasicBlockName()
{
    return this->getName() + "_BB_" + std::to_string(nextBBnumber++);
}

void CFG::setCurrentBasicBlock(BasicBlock *bb)
{
    currentBasicBlock = bb;
}

BasicBlock * CFG::getCurrentBasicBlock() const
{
    return currentBasicBlock;
}

Symbol *CFG::getLastInstructionDestination()
{
    return currentBasicBlock->getLastInstructionDestination();
}

int CFG::getOffsetFromCurrentBasicBlock()
{
    if(currentBasicBlock != nullptr)
    {
        auto pair = mapLevelData.find(currentBasicBlock->getLevel());

        if(pair != mapLevelData.end())
        {
            LevelData data = pair->second;
            data.offset++;
            updateMaximalOffset(data.offset);
            mapLevelData[currentBasicBlock->getLevel()] = data;

            return data.offset;
        }
        else
        {
            std::cout << "Error CFG::getOffsetFromCurrentBasicBlock : no level data found" << std::endl;
        }
    }
    else
    {
        std::cout << "Error CFG::getOffsetFromCurrentBasicBlock : current basic block is null" << std::endl;
    }


    return -1;
}

void CFG::incrementOffsetWithArraySize(int _size)
{
    auto pair = mapLevelData.find(currentBasicBlock->getLevel());

    if (pair != mapLevelData.end())
    {
        LevelData data = pair->second;

        if(_size < 1)
        {
            _size = 1;
        }
        
        data.offset += _size-1;
        mapLevelData[currentBasicBlock->getLevel()] = data;
    }

    std::cout << "Error CFG::incrementOffsetWithArraySize" << std::endl;
}

std::string CFG::getTempVariableName()
{
    return currentBasicBlock->getTempVariableName();
}

void CFG::addSymbolToCurrentBasicBlock(Symbol *symbole)
{
    currentBasicBlock->addLocalSymbol(symbole);
}

void CFG::setCurrentBasicBlockExitTrue(BasicBlock *bb)
{
    currentBasicBlock->setExitTrue(bb);
}

void CFG::setCurrentBasicBlockExitFalse(BasicBlock *bb)
{
    currentBasicBlock->setExitFalse(bb);
}

void CFG::addInstructionInCurrentBasicBlock(IRInstruction *instruction)
{
    currentBasicBlock->addIRInstruction(instruction);
}

void CFG::attachNewBasicBlock(BasicBlock *block)
{
    setCurrentBasicBlockExitTrue(block);
    setCurrentBasicBlock(block);
}

void CFG::setRootBasicBlock(BasicBlock *block)
{
    rootBasicBlock = block;
}

BasicBlock *CFG::getRootBasicBlock() const
{
    return rootBasicBlock;
}

CFG::LevelData *CFG::getLevelData(int level)
{
    auto pair = mapLevelData.find(level);
    if(pair == mapLevelData.end())
        return nullptr;
    else
        return &(pair->second);
}

void CFG::addNewLevelData(int level, BasicBlock * firstBlock)
{
    LevelData data;

    auto pair = mapLevelData.find(level-1);

    if(pair != mapLevelData.end())
    {
        data.offset = pair->second.offset;
        data.lastBasicBlock = firstBlock;
    }
    else
    {
        std::cout << "Error CFG::addNewLevelData : previous level data not found for level " << std::to_string(level-1) << std::endl;
        return;
    }

    mapLevelData.insert(std::pair<int,LevelData>(level,data));

    std::cout << "add New level" << std::endl;
}

int CFG::getPrologMaximalOffset()
{
    return maximalOffset;
}

void CFG::updateMaximalOffset(int offset)
{
    if(offset > maximalOffset)
        maximalOffset = offset;
}

void CFG::cleanLevel(int level)
{
    mapLevelData.erase(level);

    std::cout << "clean" << std::endl;
}

DeclarationFunction *CFG::getFunction() const
{
    return function;
}
