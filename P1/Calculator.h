#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <functional>
#include "VariableNode.h"
#include "VariableLinkedList.h"

class Calculator
{
public:
    bool define(std::string name, double value);
    bool performOperation(std::string v1, std::string v2, std::string output, std::function<double(double, double)> operation);
    bool remove(std::string name);
    void print(std::string name);
    Calculator(int cap);
    ~Calculator();

private:
    VariableLinkedList *data;
};
#endif
