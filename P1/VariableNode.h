#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include <iostream>

class VariableNode
{
public:
    std::string getName();

    double getValue();
    void setValue(double value);

    VariableNode *getNext();
    void setNext(VariableNode *next);

    VariableNode(std::string name, double value, VariableNode *next);

    void DestroyAll();

private:
    std::string name;
    double value;
    VariableNode *next;
};
#endif