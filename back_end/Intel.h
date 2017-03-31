#ifndef _INTEL_H
#define _INTEL_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "Writer.h"
#include "../middle_end/CFG.h"
#include "../middle_end/BasicBlock.h"
#include "../middle_end/IRInstruction.h"

class Intel : public Writer
{
public:
    Intel(const std::string _filename);
    ~Intel();

    void parse(CFG* _cfg);
    int compile();

    void putchar(const char character);
    void call();
    void ifThenElse();

    void test();

private:
    CFG* cfg;
};

#endif